#!/usr/bin/env python3
"""
preprocess_vn_font.py — Build VN plate character dataset from the authentic
                        Vietnamese license plate font sheet.

Source:
  /home/vinniny/projects/Lisence-Plate-Recognition-Algorithms/training_chars.png

The sheet contains 5 repetitions of the character set used on Vietnamese plates,
rendered in the actual VN license plate font:
  Row A (26 chars): A B C D E F G H K L M N P Q R S T U V X Y Z 0 1 2 3
  Row B  (6 chars): 4 5 6 7 8 9
Q and R appear in the sheet but are excluded from the 30-class VN_CHAR_MAP.

Approach:
  1. Detect all character bounding boxes via contour detection
  2. Cluster into rows, assign labels from the known sheet sequence
  3. Apply heavy augmentation to generate ~1000 training samples per class
  4. 70 / 15 / 15 train / val / test split

Output (replaces any prior processed/ splits):
  datasets/processed/train.pt  val.pt  test.pt
  datasets/processed/class_map.json
"""

import os
import sys
import json
import random
import argparse
import numpy as np
import torch
from pathlib import Path
from PIL import Image, ImageFilter

try:
    import cv2
except ImportError:
    print("ERROR: opencv-python required. pip install opencv-python")
    sys.exit(1)

# ── VN character map (must match lpr_golden.h) ────────────────────────────────

VN_CHAR_MAP = ['1','2','3','4','5','6','7','8','9',
               'A','B','C','D','E','F','G','H','K','L','M',
               'N','P','S','T','U','V','X','Y','Z','0']
assert len(VN_CHAR_MAP) == 30
CHAR_TO_IDX = {c: i for i, c in enumerate(VN_CHAR_MAP)}

# Sequence of characters as they appear in each row-pair of the sheet
SHEET_ROW_A = ['A','B','C','D','E','F','G','H','K','L','M','N','P','Q','R',
               'S','T','U','V','X','Y','Z','0','1','2','3']   # 26 chars
SHEET_ROW_B = ['4','5','6','7','8','9']                        # 6 chars
SHEET_SEQ   = SHEET_ROW_A + SHEET_ROW_B                        # 32 chars
VN_SET      = set(VN_CHAR_MAP)

IMG_SIZE    = 28


# ── Character extraction ─────────────────────────────────────────────────────

def extract_chars_from_sheet(sheet_path: Path, debug: bool = False):
    """
    Detect all character cells in the font sheet and return a list of
    (pil_image_28x28, char_label) pairs in reading order.
    """
    img_bgr  = cv2.imread(str(sheet_path))
    assert img_bgr is not None, f"Cannot read {sheet_path}"
    gray = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2GRAY)

    # Invert (chars are dark on white → make them white on black for findContours)
    _, binary = cv2.threshold(gray, 0, 255,
                              cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)

    # Dilate slightly to close small gaps within one character
    kernel = np.ones((3, 3), np.uint8)
    binary = cv2.dilate(binary, kernel, iterations=1)

    contours, _ = cv2.findContours(binary, cv2.RETR_EXTERNAL,
                                   cv2.CHAIN_APPROX_SIMPLE)

    # Collect bounding boxes, filter noise
    H, W = gray.shape
    boxes = []
    for cnt in contours:
        x, y, w, h = cv2.boundingRect(cnt)
        area = w * h
        # Rough character-size filter
        if area < 200 or w < 8 or h < 15:
            continue
        if w > W // 4 or h > H // 5:   # skip anything implausibly large
            continue
        boxes.append((x, y, w, h))

    if not boxes:
        raise RuntimeError("No character bounding boxes found in sheet — "
                           "check sheet_path or threshold.")

    print(f"[font] Found {len(boxes)} raw bounding boxes in {sheet_path.name}")

    # ── Row clustering via y-centroid ─────────────────────────────────────────
    # Sort all boxes by their y-centroid to find row boundaries.
    boxes_sorted = sorted(boxes, key=lambda b: b[1] + b[3] / 2)
    y_centers    = np.array([b[1] + b[3] / 2 for b in boxes_sorted])
    y_gaps       = np.diff(y_centers)  # gaps between consecutive y-centers

    # The 9 largest gaps separate 10 rows (5 groups × 2 rows)
    expected_rows  = 10
    n_splits       = expected_rows - 1
    split_thresh   = np.sort(y_gaps)[-n_splits]   # 9th-largest gap value
    split_indices  = np.where(y_gaps >= split_thresh)[0]

    # Build rows: each row is a list of boxes sorted by x
    rows = []
    start = 0
    for idx in sorted(split_indices):
        row = boxes_sorted[start : idx + 1]
        rows.append(sorted(row, key=lambda b: b[0]))
        start = idx + 1
    rows.append(sorted(boxes_sorted[start:], key=lambda b: b[0]))

    print(f"[font] Detected {len(rows)} rows "
          f"({[len(r) for r in rows]})")

    if len(rows) != expected_rows:
        print(f"[font] WARNING: expected {expected_rows} rows, got {len(rows)}. "
              "Adjust filtering or threshold.")

    # ── Assign labels ─────────────────────────────────────────────────────────
    # Rows alternate: A-row (26 chars) / B-row (6 chars)
    chars_out = []   # list of (pil_img_28x28, char_label)

    for row_idx, row in enumerate(rows):
        is_a_row = (row_idx % 2 == 0)
        expected = SHEET_ROW_A if is_a_row else SHEET_ROW_B

        if len(row) != len(expected):
            print(f"[font] WARNING: row {row_idx} has {len(row)} boxes, "
                  f"expected {len(expected)} ({expected[0]}..{expected[-1]})")

        for col_idx, bbox in enumerate(row):
            if col_idx >= len(expected):
                break
            char = expected[col_idx]
            if char not in VN_SET:
                continue   # skip Q, R

            x, y, w, h = bbox
            # Add a small margin
            pad = 4
            x1 = max(0, x - pad)
            y1 = max(0, y - pad)
            x2 = min(W, x + w + pad)
            y2 = min(H, y + h + pad)

            crop_bgr = img_bgr[y1:y2, x1:x2]
            crop_gray = cv2.cvtColor(crop_bgr, cv2.COLOR_BGR2GRAY)
            # Resize to 28×28
            resized = cv2.resize(crop_gray, (IMG_SIZE, IMG_SIZE),
                                 interpolation=cv2.INTER_AREA)
            pil_img = Image.fromarray(resized)
            chars_out.append((pil_img, char))

    # Group by class
    class_counts = {}
    for _, ch in chars_out:
        class_counts[ch] = class_counts.get(ch, 0) + 1

    print(f"[font] Extracted {len(chars_out)} valid character instances.")
    print(f"[font] Samples per class: {sorted(class_counts.items())}")

    if debug:
        # Save a debug grid
        _save_debug_grid(chars_out, Path("debug_extracted.png"))

    return chars_out


def _save_debug_grid(chars_out, path, cols=32):
    """Save extracted characters as a visual grid for inspection."""
    n = len(chars_out)
    rows = (n + cols - 1) // cols
    grid = Image.new('L', (cols * IMG_SIZE, rows * IMG_SIZE), 255)
    for i, (img, ch) in enumerate(chars_out):
        r, c = divmod(i, cols)
        grid.paste(img.resize((IMG_SIZE, IMG_SIZE)), (c * IMG_SIZE, r * IMG_SIZE))
    grid.save(path)
    print(f"[font] Debug grid saved to {path}")


# ── Augmentation ─────────────────────────────────────────────────────────────

def augment_one(img_pil: Image.Image, rng: np.random.RandomState) -> np.ndarray:
    """
    Apply a random combination of augmentations to a 28×28 PIL grayscale image.
    Returns a 28×28 uint8 numpy array.
    """
    # 1. Random rotation ±12°
    angle = rng.uniform(-12, 12)
    img = img_pil.rotate(angle, expand=False, fillcolor=255, resample=Image.BILINEAR)

    # 2. Random scale 0.82–1.18 (resize + recenter)
    scale = rng.uniform(0.82, 1.18)
    ns = max(4, int(IMG_SIZE * scale))
    img = img.resize((ns, ns), Image.BILINEAR)
    canvas = Image.new('L', (IMG_SIZE, IMG_SIZE), 255)
    if ns <= IMG_SIZE:
        off = (IMG_SIZE - ns) // 2
        canvas.paste(img, (off, off))
    else:
        off = (ns - IMG_SIZE) // 2
        canvas.paste(img.crop((off, off, off + IMG_SIZE, off + IMG_SIZE)), (0, 0))
    img = canvas

    # 3. Random translation ±3 px
    dx = int(rng.uniform(-3, 3))
    dy = int(rng.uniform(-3, 3))
    img = img.transform(img.size, Image.AFFINE,
                        (1, 0, -dx, 0, 1, -dy), fillcolor=255)

    arr = np.array(img, dtype=np.float32)

    # 4. Brightness / contrast on dark strokes
    #    Invert so characters are bright → scale → re-invert
    inv = 255.0 - arr
    inv = inv * rng.uniform(0.7, 1.3)
    arr = 255.0 - np.clip(inv, 0, 255)

    # 5. Gaussian noise
    sigma = rng.uniform(0, 10)
    arr = arr + rng.normal(0, sigma, arr.shape)
    arr = np.clip(arr, 0, 255)

    # 6. Optional Gaussian blur (simulate defocus / motion)
    if rng.random() < 0.35:
        arr_u8 = arr.astype(np.uint8)
        pil_blur = Image.fromarray(arr_u8).filter(
            ImageFilter.GaussianBlur(radius=rng.uniform(0.4, 1.4)))
        arr = np.array(pil_blur, dtype=np.float32)

    # 7. Optional slight shear
    if rng.random() < 0.3:
        shear = rng.uniform(-0.12, 0.12)
        arr_u8 = np.clip(arr, 0, 255).astype(np.uint8)
        pil_s = Image.fromarray(arr_u8)
        pil_s = pil_s.transform(pil_s.size, Image.AFFINE,
                                (1, shear, -shear * IMG_SIZE / 2,
                                 0, 1, 0), fillcolor=255)
        arr = np.array(pil_s, dtype=np.float32)

    return np.clip(arr, 0, 255).astype(np.uint8)


def augment_char(pil_img: Image.Image, char: str,
                 n: int = 200, seed: int = 0):
    """Generate n augmented 28×28 uint8 arrays for one character image."""
    rng = np.random.RandomState(seed)
    out = []
    # Always include the (slightly processed) original too
    arr_orig = np.array(pil_img.resize((IMG_SIZE, IMG_SIZE), Image.BILINEAR))
    out.append(arr_orig)
    for _ in range(n - 1):
        out.append(augment_one(pil_img, rng))
    return out


# ── Dataset builder ───────────────────────────────────────────────────────────

def build_dataset(chars_out, n_aug: int = 200, seed: int = 42,
                  train_frac: float = 0.70, val_frac: float = 0.15):
    """
    Augment all extracted characters and split into train/val/test.
    Returns (train_items, val_items, test_items) where each item is
    (np_uint8_28x28, label_idx).
    """
    rng_split = random.Random(seed)

    all_items = []
    for i, (pil_img, char) in enumerate(chars_out):
        label = CHAR_TO_IDX[char]
        augmented = augment_char(pil_img, char, n=n_aug, seed=seed + i * 1000)
        for arr in augmented:
            all_items.append((arr, label))

    rng_split.shuffle(all_items)

    n       = len(all_items)
    n_train = int(n * train_frac)
    n_val   = int(n * val_frac)

    train = all_items[:n_train]
    val   = all_items[n_train : n_train + n_val]
    test  = all_items[n_train + n_val:]

    return train, val, test


def pack_split(items):
    """Pack [(arr, label)] → (X_tensor [N,1,H,W] float32 [0,255], y_tensor)."""
    arrays = np.stack([x for x, _ in items], axis=0)   # [N,H,W]
    arrays = arrays[:, np.newaxis, :, :]                 # [N,1,H,W]
    X = torch.from_numpy(arrays.astype(np.float32))
    y = torch.tensor([lbl for _, lbl in items], dtype=torch.long)
    return X, y


# ── Main ──────────────────────────────────────────────────────────────────────

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--sheet', default=
        '/home/vinniny/projects/Lisence-Plate-Recognition-Algorithms/training_chars.png',
        help='Path to training_chars.png')
    parser.add_argument('--out_dir',  default='datasets/processed')
    parser.add_argument('--n_aug',    type=int, default=200,
                        help='Augmented samples per base instance (default 200)')
    parser.add_argument('--seed',     type=int, default=42)
    parser.add_argument('--debug',    action='store_true',
                        help='Save debug_extracted.png grid')
    args = parser.parse_args()

    sheet_path = Path(args.sheet)
    if not sheet_path.exists():
        print(f"ERROR: Sheet not found: {sheet_path}")
        sys.exit(1)

    out_dir = Path(args.out_dir)
    out_dir.mkdir(parents=True, exist_ok=True)

    # 1. Extract base characters from the font sheet
    chars_out = extract_chars_from_sheet(sheet_path, debug=args.debug)
    if not chars_out:
        print("ERROR: No characters extracted — check extraction parameters")
        sys.exit(1)

    n_base = len(chars_out)
    print(f"\n[font] Base instances: {n_base}")
    print(f"[font] Augmentation factor: {args.n_aug}×")
    print(f"[font] Total before split: {n_base * args.n_aug}")

    # 2. Augment and split
    train, val, test = build_dataset(
        chars_out, n_aug=args.n_aug, seed=args.seed)

    print(f"\n[font] Split  train={len(train)}  val={len(val)}  test={len(test)}")

    # 3. Save .pt files
    for name, items in [('train', train), ('val', val), ('test', test)]:
        X, y = pack_split(items)
        p = out_dir / f'{name}.pt'
        torch.save({'X': X, 'y': y}, p)
        print(f"[font] Saved {p}  X={tuple(X.shape)}  y={tuple(y.shape)}")

    # 4. Save class map
    class_map = {ch: idx for ch, idx in CHAR_TO_IDX.items()}
    map_path  = out_dir / 'class_map.json'
    with open(map_path, 'w') as f:
        json.dump({'vn_char_map': VN_CHAR_MAP,
                   'char_to_idx': class_map}, f, indent=2)
    print(f"[font] Saved {map_path}")

    # 5. Class balance report
    from collections import Counter
    y_all = [lbl for _, lbl in (train + val + test)]
    counts = Counter(y_all)
    min_c = min(counts.values())
    max_c = max(counts.values())
    print(f"\n[font] Class balance: min={min_c}  max={max_c}  "
          f"(ideal={n_base * args.n_aug // 30})")
    print("\n[font] Done. Re-run train_vn_char.py to train on this dataset.")


if __name__ == '__main__':
    main()
