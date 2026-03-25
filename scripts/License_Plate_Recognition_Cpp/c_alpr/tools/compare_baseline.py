"""
Compare C ALPR output with Python baseline.
Reads JSON output from C program and compares plate text accuracy.
"""

from pathlib import Path
import json
import sys

def compare_results(c_output_json: Path, python_baseline_json: Path) -> dict:
    """
    Compare single image results.
    Returns dict with match status and confidence diff.
    """
    try:
        with open(c_output_json) as f:
            c_result = json.load(f)
        with open(python_baseline_json) as f:
            py_result = json.load(f)
        
        c_text = c_result.get("plate_text", "").strip()
        py_text = py_result.get("plate_text", "").strip()
        
        match = c_text == py_text
        c_conf = c_result.get("plate_confidence", 0.0)
        py_conf = py_result.get("plate_confidence", 0.0)
        
        return {
            "match": match,
            "c_text": c_text,
            "py_text": py_text,
            "c_confidence": c_conf,
            "py_confidence": py_conf,
            "conf_diff": abs(c_conf - py_conf)
        }
    except Exception as e:
        print(f"Error comparing results: {e}", file=sys.stderr)
        return None

def main():
    if len(sys.argv) < 3:
        print("Usage: python compare_baseline.py c_output_dir python_baseline_dir", file=sys.stderr)
        return 1
    
    c_dir = Path(sys.argv[1])
    py_dir = Path(sys.argv[2])
    
    if not c_dir.exists() or not py_dir.exists():
        print("Directories not found", file=sys.stderr)
        return 1
    
    matches = 0
    mismatches = 0
    errors = 0
    
    for c_json in c_dir.glob("*.json"):
        img_name = c_json.stem.replace(".bmp", "")
        py_json = py_dir / f"{img_name}.json"
        
        if not py_json.exists():
            continue
        
        result = compare_results(c_json, py_json)
        if result is None:
            errors += 1
            continue
        
        if result["match"]:
            matches += 1
            print(f"✓ {img_name}: {result['c_text']}")
        else:
            mismatches += 1
            print(f"✗ {img_name}: C={result['c_text']} PY={result['py_text']}")
    
    total = matches + mismatches
    if total > 0:
        accuracy = 100.0 * matches / total
        print(f"\nAccuracy: {matches}/{total} ({accuracy:.1f}%)")
    print(f"Errors: {errors}")
    
    return 0 if mismatches == 0 else 1

if __name__ == "__main__":
    sys.exit(main())
