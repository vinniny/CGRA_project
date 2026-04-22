#!/usr/bin/env python3
"""
train_vn_char.py — Train a VN plate character classifier matching the golden topology exactly.

Network (must mirror lpr_golden.c/h):
  Input:  [N, 1, 28, 28]  float32 in [0,1]
  Conv1:  3x3, 1->8 ch,  pad=1, stride=1  + ReLU
  Pool1:  MaxPool 2x2  -> [N, 8, 14, 14]
  Conv2:  3x3, 8->16 ch, pad=1, stride=1  + ReLU
  Pool2:  MaxPool 2x2  -> [N, 16, 7, 7]
  FC:     784 -> 30 (no activation before loss)

Usage:
  python3 train_vn_char.py [--epochs 30] [--lr 1e-3] [--batch 64]
  python3 train_vn_char.py --data_dir datasets/processed --out vn_char_best.pt
"""

import argparse
import time
from pathlib import Path

import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import TensorDataset, DataLoader, WeightedRandomSampler


# ---------------------------------------------------------------------------
# Model — exact topology to match golden_infer() in lpr_golden.c
# ---------------------------------------------------------------------------

class VNCharNet(nn.Module):
    def __init__(self, num_classes=30):
        super().__init__()
        self.conv1 = nn.Conv2d(1, 8,  3, padding=1, bias=True)
        self.conv2 = nn.Conv2d(8, 16, 3, padding=1, bias=True)
        self.pool  = nn.MaxPool2d(2, 2)
        self.relu  = nn.ReLU(inplace=True)
        self.fc    = nn.Linear(16 * 7 * 7, num_classes, bias=True)

    def forward(self, x):
        x = self.pool(self.relu(self.conv1(x)))   # [N,8,14,14]
        x = self.pool(self.relu(self.conv2(x)))   # [N,16,7,7]
        x = x.view(x.size(0), -1)                  # [N,784]
        return self.fc(x)                           # [N,30]


# ---------------------------------------------------------------------------
# Data loading
# ---------------------------------------------------------------------------

def load_split(data_dir, split):
    p = Path(data_dir) / f'{split}.pt'
    if not p.exists():
        raise FileNotFoundError(f"Missing split file: {p}\n"
                                 "Run datasets/preprocess.py first.")
    d = torch.load(p, weights_only=True)
    return d['X'], d['y']


# ---------------------------------------------------------------------------
# Training
# ---------------------------------------------------------------------------

def train_epoch(model, loader, criterion, optimizer, device):
    model.train()
    total_loss = 0.0
    correct = 0
    n = 0
    for X, y in loader:
        X, y = X.to(device), y.to(device)
        optimizer.zero_grad()
        logits = model(X)
        loss = criterion(logits, y)
        loss.backward()
        optimizer.step()
        total_loss += loss.item() * len(y)
        correct += (logits.argmax(1) == y).sum().item()
        n += len(y)
    return total_loss / n, correct / n


def eval_epoch(model, loader, criterion, device):
    model.eval()
    total_loss = 0.0
    correct = 0
    n = 0
    with torch.no_grad():
        for X, y in loader:
            X, y = X.to(device), y.to(device)
            logits = model(X)
            loss = criterion(logits, y)
            total_loss += loss.item() * len(y)
            correct += (logits.argmax(1) == y).sum().item()
            n += len(y)
    return total_loss / n, correct / n


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--data_dir', default='datasets/processed')
    parser.add_argument('--out',      default='vn_char_best.pt',
                        help='Output checkpoint path')
    parser.add_argument('--epochs',   type=int,   default=30)
    parser.add_argument('--batch',    type=int,   default=64)
    parser.add_argument('--lr',       type=float, default=1e-3)
    parser.add_argument('--patience', type=int,   default=7,
                        help='Early-stop patience (val top-1 epochs)')
    parser.add_argument('--seed',     type=int,   default=42)
    args = parser.parse_args()

    torch.manual_seed(args.seed)
    device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
    print(f"[train] Device: {device}")

    # Load data
    X_train, y_train = load_split(args.data_dir, 'train')
    X_val,   y_val   = load_split(args.data_dir, 'val')
    print(f"[train] Train: {len(X_train)}, Val: {len(X_val)}")

    train_ds = TensorDataset(X_train, y_train)
    val_ds   = TensorDataset(X_val,   y_val)

    # Class-balanced sampler: counteract ~3001 digit vs ~24 letter images per class.
    # Each sample is weighted by 1/class_count so all 30 classes are equally likely.
    class_counts = torch.bincount(y_train, minlength=30).float()
    sample_weights = 1.0 / class_counts[y_train]
    sampler = WeightedRandomSampler(sample_weights, num_samples=len(y_train), replacement=True)
    print(f"[train] Class counts — min: {int(class_counts.min())}  max: {int(class_counts.max())}  (using balanced sampler)")

    train_ld = DataLoader(train_ds, batch_size=args.batch, sampler=sampler,   num_workers=0)
    val_ld   = DataLoader(val_ds,   batch_size=args.batch, shuffle=False,     num_workers=0)

    model = VNCharNet(num_classes=30).to(device)
    criterion = nn.CrossEntropyLoss()
    optimizer = optim.Adam(model.parameters(), lr=args.lr)
    scheduler = optim.lr_scheduler.ReduceLROnPlateau(optimizer, patience=3, factor=0.5)

    best_val_acc = -1.0
    no_improve   = 0
    out_path = Path(args.out)

    print(f"[train] {'Epoch':>5}  {'TrainLoss':>9}  {'TrainAcc':>8}  {'ValLoss':>9}  {'ValAcc':>8}  {'LR':>8}")
    print(f"[train] {'-'*5}  {'-'*9}  {'-'*8}  {'-'*9}  {'-'*8}  {'-'*8}")

    for epoch in range(1, args.epochs + 1):
        t0 = time.time()
        tr_loss, tr_acc = train_epoch(model, train_ld, criterion, optimizer, device)
        vl_loss, vl_acc = eval_epoch(model,  val_ld,   criterion,            device)
        scheduler.step(vl_loss)
        lr_now = optimizer.param_groups[0]['lr']
        dt = time.time() - t0

        print(f"[train] {epoch:>5}  {tr_loss:>9.4f}  {tr_acc:>7.2%}  {vl_loss:>9.4f}  {vl_acc:>7.2%}  {lr_now:>8.2e}  ({dt:.1f}s)")

        if vl_acc > best_val_acc:
            best_val_acc = vl_acc
            no_improve   = 0
            torch.save({'model_state': model.state_dict(),
                        'val_acc':     best_val_acc,
                        'epoch':       epoch,
                        'args':        vars(args)},
                       out_path)
            print(f"[train]   -> Saved best checkpoint (val_acc={vl_acc:.2%})")
        else:
            no_improve += 1
            if no_improve >= args.patience:
                print(f"[train] Early stop at epoch {epoch} (no val improvement for {args.patience} epochs)")
                break

    print(f"\n[train] Best val top-1: {best_val_acc:.2%}")
    if best_val_acc < 0.89:
        print("[train] WARNING: best val accuracy < 89% target. "
              "Consider more epochs, data augmentation, or larger dataset.")
    else:
        print("[train] Target >=89% met.")
    print(f"[train] Checkpoint: {out_path}")


if __name__ == '__main__':
    main()
