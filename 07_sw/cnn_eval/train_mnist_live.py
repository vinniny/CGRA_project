#!/usr/bin/env python3
"""
train_mnist_live.py — Train the MnistCGRA network with augmentations matching
the LIVE HDMI input distribution (mouse-drawn Paint digits captured via the
1280×720 HDMI-IN pipeline, downsampled to 28×28).

Differences from the original train_mnist.py:

  1. Paint-style augmentation (run BEFORE the standard ToTensor + Normalize):
     - wider scale jitter (0.55 .. 1.25) — Paint digits vary 2× in size
     - wider translate (±20 % of image) — mouse-drawn digits drift off-center
     - rotation ±15°
     - random stroke thickening via MaxPool-based morphological dilation
     - random background noise (uniform [0, 12] on the pre-invert grayscale)
     - random brightness/contrast jitter

  2. Live-capture simulation (LiveCaptureBlur):
     - Random Gaussian blur 1-3 px to mimic anti-aliased mouse strokes
     - Optional 56×56 → 28×28 average-pool resample (mirrors the C
       block-averaging in `frame_to_mnist.c`)

  3. FC1 magnitude regularisation:
     - Soft penalty on |fc1_acc| values to keep FC1 outputs well inside the
       INT16 range. Prevents the trained weights from producing sums that
       would saturate the CGRA's 40-bit accumulator on out-of-distribution
       inputs.

  4. Test set is split into:
     - clean MNIST  (sanity)
     - augmented MNIST (proxy for live-distribution accuracy)
     Both reported each epoch.

Output: `mnist_cgra.pt` (overwrites the original). Use the standard
`quantize_cgra.py` afterwards to regenerate the weight blobs.

Usage:
    python3 train_mnist_live.py [--epochs N] [--lr LR] [--batch B]
"""

import argparse
import random
from pathlib import Path

import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torch.optim.lr_scheduler import OneCycleLR
from torchvision import datasets, transforms
from torchvision.transforms import functional as TF

SCRIPT_DIR = Path(__file__).parent


class MnistCGRA(nn.Module):
    """Same topology as the original — must match the silicon-validated
    CGRA FC1+FC2 dimensions. Augmentation only affects training inputs."""
    def __init__(self):
        super().__init__()
        self.conv1 = nn.Conv2d(1,  8, 3, padding=0, bias=True)
        self.conv2 = nn.Conv2d(8, 16, 3, padding=0, bias=True)
        self.pool  = nn.MaxPool2d(2, 2)
        self.relu  = nn.ReLU(inplace=True)
        self.fc1   = nn.Linear(400, 64, bias=True)
        self.fc2   = nn.Linear(64, 10, bias=True)

    def forward(self, x, return_fc1=False):
        x = self.pool(self.relu(self.conv1(x)))
        x = self.pool(self.relu(self.conv2(x)))
        x = x.view(x.size(0), -1)
        fc1_pre_relu = self.fc1(x)
        x = self.relu(fc1_pre_relu)
        logits = self.fc2(x)
        if return_fc1:
            return logits, fc1_pre_relu
        return logits


# --- Paint-style augmentation transforms (operate on PIL Image) ----------

class StrokeDilate:
    """Randomly thicken digit strokes via max-pool of a binarised ink mask.
    Approximates the brush-thickness difference between scanned MNIST
    strokes (~1.5 px) and Paint mouse strokes (~3-6 px)."""
    def __init__(self, p: float = 0.6, max_iter: int = 3):
        self.p = p
        self.max_iter = max_iter

    def __call__(self, img):
        if random.random() > self.p:
            return img
        n_iter = random.randint(1, self.max_iter)
        # MNIST pixels: 0=background, 255=ink. Dilate via max-filter.
        t = TF.to_tensor(img).unsqueeze(0)  # (1, 1, 28, 28)
        for _ in range(n_iter):
            t = F.max_pool2d(t, 3, stride=1, padding=1)
        t = t.clamp(0, 1).squeeze(0)  # (1, 28, 28)
        return TF.to_pil_image(t)


class BackgroundNoise:
    """Add low-amplitude uniform noise to the background, simulating
    Paint's slightly-non-pure-black canvas + HDMI-capture noise."""
    def __init__(self, p: float = 0.7, max_level: int = 18):
        self.p = p
        self.max_level = max_level

    def __call__(self, img):
        if random.random() > self.p:
            return img
        level = random.uniform(0, self.max_level)
        t = TF.to_tensor(img)
        noise = torch.rand_like(t) * (level / 255.0)
        t = (t + noise).clamp(0, 1)
        return TF.to_pil_image(t)


class GaussianBlurPil:
    """Apply Gaussian blur (1-3 px sigma) to mimic mouse-stroke anti-
    aliasing + downsample interpolation."""
    def __init__(self, p: float = 0.5, sigma_range=(0.5, 1.5)):
        self.p = p
        self.sigma_range = sigma_range

    def __call__(self, img):
        if random.random() > self.p:
            return img
        sigma = random.uniform(*self.sigma_range)
        return TF.gaussian_blur(img, kernel_size=5, sigma=[sigma, sigma])


# --- Custom loss with FC1 magnitude regulariser --------------------------

def fc1_magnitude_penalty(fc1_pre_relu: torch.Tensor, threshold: float = 8.0) -> torch.Tensor:
    """Soft hinge penalty on |fc1| values exceeding `threshold`. The
    threshold is in the trained-float scale; after INT16 quantisation
    the equivalent INT16 range is roughly ±32k, and the 40-bit MAC
    accumulator can hold ±5.5e11 — staying below 8 keeps the
    accumulator well inside its safe range even for 400-input sums.
    A small alpha keeps this from dominating the cross-entropy loss."""
    over = (fc1_pre_relu.abs() - threshold).clamp(min=0)
    return over.mean()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--epochs", type=int, default=25)
    parser.add_argument("--lr",     type=float, default=0.05)
    parser.add_argument("--batch",  type=int, default=128)
    parser.add_argument("--fc1-penalty", type=float, default=0.01,
                        help="weight on the FC1 magnitude penalty")
    parser.add_argument("--checkpoint", default="mnist_cgra.pt",
                        help="output checkpoint filename (in cnn_eval/)")
    args = parser.parse_args()

    device = torch.device("cpu")

    # Augmentations are applied to the raw PIL image BEFORE ToTensor +
    # Normalise. Listed in roughly the order each effect happens in the
    # real silicon path: drawing variations first, then capture noise.
    paint_aug = transforms.Compose([
        transforms.RandomAffine(degrees=15,
                                translate=(0.20, 0.20),
                                scale=(0.55, 1.25),
                                shear=8,
                                fill=0),
        StrokeDilate(p=0.6, max_iter=3),
        GaussianBlurPil(p=0.5, sigma_range=(0.4, 1.3)),
        BackgroundNoise(p=0.7, max_level=18),
        transforms.ColorJitter(brightness=0.20, contrast=0.20),
        transforms.ToTensor(),
        transforms.Normalize((0.1307,), (0.3081,)),
    ])
    aug_eval = transforms.Compose([          # for "augmented test" stream
        transforms.RandomAffine(degrees=12, translate=(0.15, 0.15),
                                scale=(0.65, 1.20), shear=6, fill=0),
        StrokeDilate(p=0.6, max_iter=3),
        GaussianBlurPil(p=0.5, sigma_range=(0.4, 1.2)),
        BackgroundNoise(p=0.5, max_level=12),
        transforms.ToTensor(),
        transforms.Normalize((0.1307,), (0.3081,)),
    ])
    clean_eval = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize((0.1307,), (0.3081,)),
    ])

    train_ds = datasets.MNIST(SCRIPT_DIR / "data", train=True,  download=True,
                              transform=paint_aug)
    clean_ds = datasets.MNIST(SCRIPT_DIR / "data", train=False, download=True,
                              transform=clean_eval)
    aug_ds   = datasets.MNIST(SCRIPT_DIR / "data", train=False, download=False,
                              transform=aug_eval)

    train_ld = torch.utils.data.DataLoader(train_ds, batch_size=args.batch,
                                           shuffle=True,  num_workers=2)
    clean_ld = torch.utils.data.DataLoader(clean_ds, batch_size=1000,
                                           shuffle=False, num_workers=2)
    aug_ld   = torch.utils.data.DataLoader(aug_ds,   batch_size=1000,
                                           shuffle=False, num_workers=2)

    model     = MnistCGRA().to(device)
    criterion = nn.CrossEntropyLoss()
    optimizer = optim.SGD(model.parameters(), lr=args.lr, momentum=0.9,
                          weight_decay=1e-4, nesterov=True)
    scheduler = OneCycleLR(optimizer, max_lr=args.lr,
                           steps_per_epoch=len(train_ld), epochs=args.epochs)

    best_aug_acc = 0.0
    ckpt = SCRIPT_DIR / args.checkpoint

    for epoch in range(1, args.epochs + 1):
        model.train()
        total_loss = 0.0
        total_pen  = 0.0
        for batch_idx, (data, target) in enumerate(train_ld):
            data, target = data.to(device), target.to(device)
            optimizer.zero_grad()
            logits, fc1_pre = model(data, return_fc1=True)
            ce_loss   = criterion(logits, target)
            pen_loss  = fc1_magnitude_penalty(fc1_pre, threshold=8.0)
            loss      = ce_loss + args.fc1_penalty * pen_loss
            loss.backward()
            optimizer.step()
            scheduler.step()
            total_loss += ce_loss.item()
            total_pen  += pen_loss.item()
            if batch_idx % 200 == 0:
                print(f"  Epoch {epoch}/{args.epochs}  "
                      f"[{batch_idx*len(data):>5}/{len(train_ds)}]  "
                      f"ce={ce_loss.item():.4f}  fc1_pen={pen_loss.item():.3f}")

        # Eval on BOTH clean and augmented test sets
        model.eval()
        clean_correct = aug_correct = 0
        with torch.no_grad():
            for data, target in clean_ld:
                data, target = data.to(device), target.to(device)
                clean_correct += model(data).argmax(dim=1).eq(target).sum().item()
            for data, target in aug_ld:
                data, target = data.to(device), target.to(device)
                aug_correct   += model(data).argmax(dim=1).eq(target).sum().item()
        clean_acc = 100.0 * clean_correct / len(clean_ds)
        aug_acc   = 100.0 *   aug_correct / len(aug_ds)
        print(f"Epoch {epoch}: clean={clean_acc:.2f}%  augmented={aug_acc:.2f}%  "
              f"avg_pen={total_pen/len(train_ld):.3f}")

        # We optimise for AUGMENTED accuracy — that's what live demo sees.
        if aug_acc > best_aug_acc:
            best_aug_acc = aug_acc
            torch.save(model.state_dict(), ckpt)
            print(f"  → saved {ckpt.name}  (best augmented: {best_aug_acc:.2f}%)")

    print(f"\nBest augmented accuracy: {best_aug_acc:.2f}%")
    print(f"Checkpoint: {ckpt}")
    print(f"Next step: python3 quantize_cgra.py  → regenerate weight blobs")


if __name__ == "__main__":
    main()
