#!/usr/bin/env bash
# Fetches the duydieunguyen/licenseplates Kaggle dataset and unpacks it
# into datasets/raw/. Requires KAGGLE_USERNAME + KAGGLE_KEY env vars OR
# a valid ~/.config/kaggle/kaggle.json (standard kaggle CLI auth).
#
# Usage:  bash fetch_vn_chars.sh
# Output: datasets/raw/licenseplates/  (character crop sub-dirs)

set -euo pipefail
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
RAW_DIR="$SCRIPT_DIR/raw"
DATASET="duydieunguyen/licenseplates"
ZIP_FILE="$SCRIPT_DIR/licenseplates.zip"

echo "[fetch] Dataset: $DATASET"
echo "[fetch] Raw dir: $RAW_DIR"

if [ -d "$RAW_DIR/licenseplates" ]; then
    echo "[fetch] Raw dataset already present — skipping download."
    echo "[fetch] Delete $RAW_DIR/licenseplates to force re-download."
    exit 0
fi

# --- Option 1: kaggle CLI ---
if command -v kaggle &>/dev/null; then
    echo "[fetch] Using kaggle CLI..."
    mkdir -p "$RAW_DIR"
    kaggle datasets download -d "$DATASET" -p "$SCRIPT_DIR" --unzip
    # kaggle --unzip extracts directly under $SCRIPT_DIR; move to raw/
    if [ -d "$SCRIPT_DIR/licenseplates" ]; then
        mv "$SCRIPT_DIR/licenseplates" "$RAW_DIR/"
    fi
    echo "[fetch] Done via kaggle CLI."
    exit 0
fi

# --- Option 2: curl with Kaggle API ---
if [ -f "$HOME/.config/kaggle/kaggle.json" ]; then
    echo "[fetch] Using curl + Kaggle API..."
    USER=$(python3 -c "import json; d=json.load(open('$HOME/.config/kaggle/kaggle.json')); print(d['username'])")
    KEY=$(python3 -c "import json; d=json.load(open('$HOME/.config/kaggle/kaggle.json')); print(d['key'])")
    curl -L -u "$USER:$KEY" \
        "https://www.kaggle.com/api/v1/datasets/download/$DATASET" \
        -o "$ZIP_FILE"
    mkdir -p "$RAW_DIR"
    unzip -q "$ZIP_FILE" -d "$RAW_DIR"
    rm -f "$ZIP_FILE"
    echo "[fetch] Done via curl."
    exit 0
fi

cat <<'EOF'
[fetch] ERROR: Neither kaggle CLI nor ~/.config/kaggle/kaggle.json found.

To authenticate:
  1. Go to https://www.kaggle.com/settings -> "API" -> "Create New Token"
  2. Save the downloaded kaggle.json to ~/.config/kaggle/kaggle.json
  3. pip install kaggle
  4. Re-run this script

Alternatively, download manually:
  https://www.kaggle.com/datasets/duydieunguyen/licenseplates
  Unzip to: datasets/raw/licenseplates/
EOF
exit 1
