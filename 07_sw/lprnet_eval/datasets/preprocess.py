#!/usr/bin/env python3
"""
preprocess.py — Build train/val/test tensor splits for VN plate char recognition.

Input:  datasets/raw/licenseplates/<class_dir>/<image_files>
Output: datasets/processed/train.pt, val.pt, test.pt
        datasets/processed/class_map.json  (dataset_label -> VN_CHAR_MAP index)

VN_CHAR_MAP (30 classes, must match lpr_golden.h):
  Index 0-8:  '1'-'9'
  Index 9-28: 'A','B','C','D','E','F','G','H','K','L','M','N','P','S','T','U','V','X','Y','Z'
  Index 29:   '0'
"""

import os
import json
import random
import argparse
from pathlib import Path
from PIL import Image
import numpy as np
import torch

# Must match lpr_golden.h VN_CHAR_MAP exactly
VN_CHAR_MAP = ['1','2','3','4','5','6','7','8','9',
               'A','B','C','D','E','F','G','H','K','L','M',
               'N','P','S','T','U','V','X','Y','Z','0']
assert len(VN_CHAR_MAP) == 30

CHAR_TO_IDX = {c: i for i, c in enumerate(VN_CHAR_MAP)}

IMG_H = 28
IMG_W = 28
IMG_C = 1  # grayscale

TRAIN_FRAC = 0.70
VAL_FRAC   = 0.15
# test = remaining 0.15

def load_image(path):
    """Load image as 28x28 grayscale uint8 numpy array [H,W]."""
    img = Image.open(path).convert('L')
    img = img.resize((IMG_W, IMG_H), Image.BILINEAR)
    return np.array(img, dtype=np.uint8)

def discover_classes(raw_dir):
    """
    Walk raw_dir and find all class directories.
    Returns list of (dir_path, char_label) for recognized VN plate chars.
    Handles multiple naming conventions:
      - Directory named by char: '0', '1', ..., 'A', 'B', ...
      - Directory named by index: '00', '01', ...
      - Mixed case: 'a', 'b', ... (uppercased)
    """
    raw_dir = Path(raw_dir)
    classes = []

    # Try direct char-named subdirs first
    for d in sorted(raw_dir.iterdir()):
        if not d.is_dir():
            continue
        name = d.name.upper().strip()
        # Strip common prefixes: 'CLASS_A' -> 'A', 'CHAR_1' -> '1'
        for prefix in ('CLASS_', 'CHAR_', 'LABEL_'):
            if name.startswith(prefix):
                name = name[len(prefix):]
                break
        # Single char match
        if name in CHAR_TO_IDX:
            classes.append((d, name))
            continue
        # Try stripping leading zeros for numeric dirs like '00' -> '0'
        stripped = name.lstrip('0') or '0'
        if stripped in CHAR_TO_IDX:
            classes.append((d, stripped))
            continue
        # Numeric index (0-29) mapped via VN_CHAR_MAP
        try:
            idx = int(name)
            if 0 <= idx < 30:
                classes.append((d, VN_CHAR_MAP[idx]))
                continue
        except ValueError:
            pass
        print(f"[preprocess] WARNING: skipping unrecognized dir: {d.name!r}")

    return classes

def build_splits(raw_dir, seed=42):
    raw_dir = Path(raw_dir)
    class_dirs = discover_classes(raw_dir)
    if not class_dirs:
        raise RuntimeError(f"No recognized class directories found in {raw_dir}")

    print(f"[preprocess] Found {len(class_dirs)} classes in {raw_dir}")

    all_images = []  # list of (np_array, label_idx)
    class_map = {}   # dir_name -> VN_CHAR_MAP index

    img_exts = {'.jpg', '.jpeg', '.png', '.bmp', '.ppm'}

    for d, char in class_dirs:
        idx = CHAR_TO_IDX[char]
        class_map[d.name] = idx
        paths = [p for p in d.iterdir() if p.suffix.lower() in img_exts]
        for p in paths:
            try:
                arr = load_image(p)
                all_images.append((arr, idx))
            except Exception as e:
                print(f"[preprocess] WARNING: could not load {p}: {e}")

    print(f"[preprocess] Total images: {len(all_images)}")
    if not all_images:
        raise RuntimeError("No images loaded — check raw_dir structure")

    rng = random.Random(seed)
    rng.shuffle(all_images)

    n = len(all_images)
    n_train = int(n * TRAIN_FRAC)
    n_val   = int(n * VAL_FRAC)

    splits = {
        'train': all_images[:n_train],
        'val':   all_images[n_train:n_train + n_val],
        'test':  all_images[n_train + n_val:],
    }

    for name, items in splits.items():
        print(f"[preprocess]   {name}: {len(items)} images")

    return splits, class_map

def pack_split(items):
    """Pack list of (array, label) into (X_tensor, y_tensor).
    X: float32 [N, 1, H, W] in [0.0, 255.0] — matches golden_infer() int32 [0-255] input.
    y: int64   [N]
    """
    arrays = np.stack([x for x, _ in items], axis=0)          # [N, H, W]
    arrays = arrays[:, np.newaxis, :, :]                        # [N, 1, H, W]
    X = torch.from_numpy(arrays.astype(np.float32))            # keep [0, 255] range
    y = torch.tensor([lbl for _, lbl in items], dtype=torch.long)
    return X, y

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--raw_dir',   default='datasets/raw/licenseplates',
                        help='Root dir of raw dataset')
    parser.add_argument('--out_dir',   default='datasets/processed',
                        help='Output directory for .pt splits')
    parser.add_argument('--seed',      type=int, default=42)
    args = parser.parse_args()

    out_dir = Path(args.out_dir)
    out_dir.mkdir(parents=True, exist_ok=True)

    splits, class_map = build_splits(args.raw_dir, seed=args.seed)

    for name, items in splits.items():
        X, y = pack_split(items)
        out_path = out_dir / f'{name}.pt'
        torch.save({'X': X, 'y': y}, out_path)
        print(f"[preprocess] Saved {out_path}  (X={tuple(X.shape)}, y={tuple(y.shape)})")

    map_path = out_dir / 'class_map.json'
    with open(map_path, 'w') as f:
        json.dump({'dir_to_vn_idx': class_map,
                   'vn_char_map': VN_CHAR_MAP}, f, indent=2)
    print(f"[preprocess] Saved {map_path}")

if __name__ == '__main__':
    main()
