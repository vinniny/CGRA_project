"""
Generate Python baseline ALPR results in JSON format for comparison with C implementation.
This script runs the Python YOLO models on test images and outputs results as JSON.
"""

import json
import os
from pathlib import Path
import sys
import cv2
from ultralytics import YOLO

def load_char_map():
    """Load character mapping from config_character.yaml"""
    char_map = {}
    try:
        import yaml
        root = Path(__file__).resolve().parents[2]
        config_path = root / "config_character.yaml"
        with open(config_path, 'r') as f:
            cfg = yaml.safe_load(f)
            if cfg and 'names' in cfg:
                for class_id, char in cfg['names'].items():
                    char_map[class_id] = char
    except:
        # Fallback hardcoded mapping matching config_character.yaml
        char_map = {
            0: '1', 1: '2', 2: '3', 3: '4', 4: '5',
            5: '6', 6: '7', 7: '8', 8: '9', 9: '0',
            10: 'A', 11: 'B', 12: 'C', 13: 'D', 14: 'E',
            15: 'F', 16: 'G', 17: 'H', 18: 'K', 19: 'L',
            20: 'M', 21: 'N', 22: 'P', 23: 'S', 24: 'T',
            25: 'U', 26: 'V', 27: 'X', 28: 'Y', 29: 'Z'
        }
    return char_map

def assemble_plate_text_one_line(char_detections):
    """
    Assemble single-line plate by sorting left-to-right and inserting dash.
    Format: 1-2ABC or similar, where dash appears before first alpha.
    """
    if not char_detections:
        return ""
    
    # Sort by x coordinate (left to right)
    sorted_chars = sorted(char_detections, key=lambda x: x['x'])
    
    chars = [c['char'] for c in sorted_chars]
    
    # Find first alphabetic character position
    first_alpha_idx = -1
    for i, c in enumerate(chars):
        if c.isalpha():
            first_alpha_idx = i
            break
    
    # Build text with dash before first letter
    if first_alpha_idx > 0:
        result = ''.join(chars[:first_alpha_idx]) + '-' + ''.join(chars[first_alpha_idx:])
    else:
        result = ''.join(chars)
    
    return result

def assemble_plate_text_two_line(char_detections):
    """
    Assemble two-line plate by splitting horizontally at mean y-coordinate.
    """
    if len(char_detections) < 2:
        return assemble_plate_text_one_line(char_detections)
    
    # Calculate mean y position
    mean_y = sum(c['y'] for c in char_detections) / len(char_detections)
    
    # Split into top and bottom lines based on mean_y
    top_chars = [c for c in char_detections if c['y'] < mean_y]
    bot_chars = [c for c in char_detections if c['y'] >= mean_y]
    
    # Assemble each line
    top_text = assemble_plate_text_one_line(top_chars) if top_chars else ""
    bot_text = assemble_plate_text_one_line(bot_chars) if bot_chars else ""
    
    return f"{top_text}\n{bot_text}" if bot_text else top_text

def detect_characters(crop, model_char, char_map, confidence_threshold=0.3):
    """Detect characters within a license plate crop"""
    results = model_char(crop)[0]
    
    char_detections = []
    for bbox in (results.boxes.data.tolist() if results.boxes is not None else []):
        x1, y1, x2, y2, conf, cls_id = bbox
        if conf > confidence_threshold:
            center_x = (x1 + x2) / 2
            center_y = (y1 + y2) / 2
            cls_id = int(cls_id)
            char = char_map.get(cls_id, f"?{cls_id}")
            char_detections.append({
                'char': char,
                'x': center_x,
                'y': center_y,
                'confidence': conf,
                'class_id': cls_id
            })
    
    return char_detections

def process_image(image_path, model_plate, model_char, char_map, plate_confidence_threshold=0.5):
    """
    Process single image and return ALPR result.
    Returns dict with image_path, error_code, plate_text, plate_confidence, plate_type
    """
    result = {
        'image_path': str(image_path),
        'error_code': 0,
        'plate_text': '',
        'plate_confidence': 0.0,
        'plate_type': 'unknown',  # 'one_line', 'two_line', 'unknown'
        'details': {}
    }
    
    try:
        img = cv2.imread(str(image_path))
        if img is None:
            result['error_code'] = -1  # Cannot read image
            return result
        
        # Detect plates
        plate_results = model_plate(img)[0]
        
        if plate_results.boxes is None or len(plate_results.boxes) == 0:
            result['error_code'] = 1  # No plates detected
            return result
        
        # Process best plate (highest confidence)
        best_plate = None
        best_conf = 0
        best_coords = None
        
        for bbox in plate_results.boxes.data.tolist():
            x1, y1, x2, y2, conf, cls_id = bbox
            if conf > plate_confidence_threshold and conf > best_conf:
                best_conf = conf
                best_plate = bbox
                best_coords = (int(x1), int(y1), int(x2), int(y2))
        
        if best_plate is None:
            result['error_code'] = 1  # No plates above threshold
            return result
        
        x1, y1, x2, y2 = best_coords
        
        # Crop plate region with small margin
        margin = 2
        crop_x1 = max(0, x1 - margin)
        crop_y1 = max(0, y1 - margin)
        crop_x2 = min(img.shape[1], x2 + margin)
        crop_y2 = min(img.shape[0], y2 + margin)
        
        crop = img[crop_y1:crop_y2, crop_x1:crop_x2]
        if crop.size == 0:
            result['error_code'] = 2  # Invalid crop
            return result
        
        # Scale up small plates for better character detection
        h, w = crop.shape[:2]
        if w < 100:
            scale = 5 if w < 60 else 4
            crop = cv2.resize(crop, (w * scale, h * scale), interpolation=cv2.INTER_LINEAR)
        
        # Detect characters
        char_detections = detect_characters(crop, model_char, char_map)
        
        if not char_detections:
            result['error_code'] = 3  # No characters detected
            return result
        
        # Determine plate type and assemble text
        mean_y = sum(c['y'] for c in char_detections) / len(char_detections)
        y_variation = [abs(c['y'] - mean_y) for c in char_detections]
        max_y_var = max(y_variation) if y_variation else 0
        
        # If high vertical spread, treat as two-line
        if max_y_var > 30:
            plate_text = assemble_plate_text_two_line(char_detections)
            result['plate_type'] = 'two_line'
        else:
            plate_text = assemble_plate_text_one_line(char_detections)
            result['plate_type'] = 'one_line'
        
        # Calculate overall confidence as mean of character confidences
        avg_char_conf = sum(c['confidence'] for c in char_detections) / len(char_detections)
        
        result['plate_text'] = plate_text
        result['plate_confidence'] = float(best_conf)  # Use plate detection confidence
        result['error_code'] = 0
        result['details'] = {
            'num_characters': len(char_detections),
            'plate_detection_confidence': float(best_conf),
            'character_mean_confidence': float(avg_char_conf),
            'plate_bbox': {
                'x1': x1, 'y1': y1, 'x2': x2, 'y2': y2,
                'width': x2 - x1, 'height': y2 - y1
            }
        }
        
    except Exception as e:
        result['error_code'] = -2
        result['details'] = {'exception': str(e)}
    
    return result

def main():
    root = Path(__file__).resolve().parents[2]
    
    # Model paths
    model_plate_path = root / "runs" / "detect" / "train" / "weights" / "last.pt"
    model_char_path = root / "runs" / "detect" / "train2" / "weights" / "last.pt"
    
    # Input and output directories
    input_dir = root / "c_alpr" / "test_images"
    output_dir = root / "output" / "baseline_python"
    
    if not model_plate_path.exists():
        print(f"ERROR: Plate model not found at {model_plate_path}")
        print(f"Please run: python c_alpr/tools/export_onnx.py first")
        return 1
    
    if not model_char_path.exists():
        print(f"ERROR: Character model not found at {model_char_path}")
        return 1
    
    if not input_dir.exists():
        print(f"ERROR: Input directory not found at {input_dir}")
        print(f"Please run: python c_alpr/tools/convert_to_bmp24.py first")
        return 1
    
    output_dir.mkdir(parents=True, exist_ok=True)
    
    # Load models
    print(f"Loading plate detection model from {model_plate_path}...")
    model_plate = YOLO(str(model_plate_path))
    
    print(f"Loading character detection model from {model_char_path}...")
    model_char = YOLO(str(model_char_path))
    
    # Load character mapping
    char_map = load_char_map()
    print(f"Loaded character map with {len(char_map)} classes")
    
    # Process all images
    image_files = list(input_dir.glob("*.bmp"))
    if not image_files:
        print(f"No BMP files found in {input_dir}")
        return 1
    
    print(f"Processing {len(image_files)} images...")
    
    processed = 0
    for img_file in sorted(image_files):
        result = process_image(img_file, model_plate, model_char, char_map)
        
        # Save JSON result
        json_path = output_dir / (img_file.stem + ".json")
        with open(json_path, 'w') as f:
            json.dump(result, f, indent=2)
        
        processed += 1
        if processed % 50 == 0:
            print(f"  Processed {processed}/{len(image_files)}...")
    
    print(f"Done. Generated {processed} JSON result files in {output_dir}")
    return 0

if __name__ == "__main__":
    sys.exit(main())
