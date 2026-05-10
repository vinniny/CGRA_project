#!/usr/bin/env python3
"""
train_mnist.py — Train a small CNN on MNIST for CGRA demo.

Architecture (no padding, matches Cat14 validated conv sizes):
  28×28 INT input
  → Conv2d(1,  8, 3, padding=0)  → 26×26×8
  → ReLU + MaxPool2d(2,2)        → 13×13×8
  → Conv2d(8, 16, 3, padding=0)  → 11×11×16
  → ReLU + MaxPool2d(2,2)        → 5×5×16
  → Linear(400, 64) + ReLU
  → Linear(64, 10)

Target: ≥99% test accuracy.

Output: mnist_cgra.pt  (float32 state dict)

Usage:
    python3 train_mnist.py [--epochs N] [--lr LR] [--batch B]
"""

import argparse
import torch
import torch.nn as nn
import torch.optim as optim
from torch.optim.lr_scheduler import CosineAnnealingLR
from torchvision import datasets, transforms
from pathlib import Path

SCRIPT_DIR = Path(__file__).parent


class MnistCGRA(nn.Module):
    def __init__(self):
        super().__init__()
        self.conv1 = nn.Conv2d(1, 8, 3, padding=0, bias=True)
        self.conv2 = nn.Conv2d(8, 16, 3, padding=0, bias=True)
        self.pool  = nn.MaxPool2d(2, 2)
        self.relu  = nn.ReLU(inplace=True)
        self.fc1   = nn.Linear(400, 64, bias=True)
        self.fc2   = nn.Linear(64, 10, bias=True)

    def forward(self, x):
        x = self.pool(self.relu(self.conv1(x)))  # 26×26×8 → 13×13×8
        x = self.pool(self.relu(self.conv2(x)))  # 11×11×16 → 5×5×16
        x = x.view(x.size(0), -1)               # 400
        x = self.relu(self.fc1(x))               # 64
        return self.fc2(x)                        # 10


def train(args):
    device = torch.device("cpu")

    aug_transform = transforms.Compose([
        transforms.RandomAffine(degrees=5, translate=(0.1, 0.1), scale=(0.9, 1.1)),
        transforms.ToTensor(),
        transforms.Normalize((0.1307,), (0.3081,)),
    ])
    eval_transform = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize((0.1307,), (0.3081,)),
    ])
    train_ds = datasets.MNIST(SCRIPT_DIR / "data", train=True,  download=True, transform=aug_transform)
    test_ds  = datasets.MNIST(SCRIPT_DIR / "data", train=False, download=True, transform=eval_transform)
    train_ld = torch.utils.data.DataLoader(train_ds, batch_size=args.batch, shuffle=True,  num_workers=2)
    test_ld  = torch.utils.data.DataLoader(test_ds,  batch_size=1000,       shuffle=False, num_workers=2)

    model = MnistCGRA().to(device)
    criterion = nn.CrossEntropyLoss()
    optimizer = optim.SGD(model.parameters(), lr=args.lr, momentum=0.9,
                          weight_decay=1e-4, nesterov=True)
    from torch.optim.lr_scheduler import OneCycleLR
    scheduler = OneCycleLR(optimizer, max_lr=args.lr,
                           steps_per_epoch=len(train_ld), epochs=args.epochs)

    best_acc = 0.0
    for epoch in range(1, args.epochs + 1):
        model.train()
        for batch_idx, (data, target) in enumerate(train_ld):
            data, target = data.to(device), target.to(device)
            optimizer.zero_grad()
            output = model(data)
            loss = criterion(output, target)
            loss.backward()
            optimizer.step()
            scheduler.step()  # OneCycleLR steps per batch
            if batch_idx % 200 == 0:
                print(f"  Epoch {epoch}/{args.epochs}  "
                      f"[{batch_idx*len(data)}/{len(train_ds)}]  loss={loss.item():.4f}")

        model.eval()
        correct = 0
        with torch.no_grad():
            for data, target in test_ld:
                data, target = data.to(device), target.to(device)
                pred = model(data).argmax(dim=1)
                correct += pred.eq(target).sum().item()
        acc = 100.0 * correct / len(test_ds)
        print(f"Epoch {epoch}: test accuracy = {acc:.2f}%")
        if acc > best_acc:
            best_acc = acc
            torch.save(model.state_dict(), SCRIPT_DIR / "mnist_cgra.pt")
            print(f"  → Saved (best so far)")
        else:
            pass  # keep going

    print(f"\nBest test accuracy: {best_acc:.2f}%")
    if best_acc < 99.0:
        print("WARNING: target is ≥99%% — consider more epochs or lower LR")
    return best_acc


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--epochs", type=int, default=20)
    parser.add_argument("--lr",     type=float, default=0.05)
    parser.add_argument("--batch",  type=int, default=128)
    args = parser.parse_args()
    train(args)
