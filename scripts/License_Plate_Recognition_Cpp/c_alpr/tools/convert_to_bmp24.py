"""
Convert images from data/license_plate/images/train to BMP 24-bit format.
This allows the C ALPR pipeline to process them since BMP 24-bit is supported.
"""

from pathlib import Path
from PIL import Image
import sys

def convert_to_bmp24(image_path: Path, output_path: Path) -> bool:
    try:
        img = Image.open(image_path)
        if img.mode != 'RGB':
            img = img.convert('RGB')
        img.save(output_path, format='BMP')
        return True
    except Exception as e:
        print(f"Error converting {image_path}: {e}", file=sys.stderr)
        return False

def main():
    root = Path(__file__).resolve().parents[2]
    input_dir = root / "data" / "license_plate" / "images" / "train"
    output_dir = root / "c_alpr" / "test_images"
    
    if not input_dir.exists():
        print(f"Input directory not found: {input_dir}")
        return 1
    
    output_dir.mkdir(parents=True, exist_ok=True)
    
    converted = 0
    for img_file in input_dir.glob("*"):
        if img_file.is_file() and img_file.suffix.lower() in ['.jpg', '.jpeg', '.png', '.bmp']:
            out_path = output_dir / (img_file.stem + ".bmp")
            if convert_to_bmp24(img_file, out_path):
                converted += 1
                if converted % 10 == 0:
                    print(f"Converted {converted} images...")
    
    print(f"Done. Converted {converted} images to {output_dir}")
    return 0

if __name__ == "__main__":
    sys.exit(main())
