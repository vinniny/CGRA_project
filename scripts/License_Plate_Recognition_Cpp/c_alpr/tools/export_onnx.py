from pathlib import Path
from ultralytics import YOLO

ROOT = Path(__file__).resolve().parents[2]
MODELS_DIR = ROOT / "c_alpr" / "models"
MODELS_DIR.mkdir(parents=True, exist_ok=True)

PLATE_PT = ROOT / "runs" / "detect" / "train" / "weights" / "last.pt"
CHAR_PT = ROOT / "runs" / "detect" / "train2" / "weights" / "last.pt"


def export_one(pt_path: Path, out_name: str, imgsz: int = 640):
    if not pt_path.exists():
        raise FileNotFoundError(f"Missing model: {pt_path}")

    model = YOLO(str(pt_path))
    # NOTE: simplify=True may hang on some Windows/Python environments (onnxslim stage).
    # Export robustly first; model optimization can be done later if needed.
    exported_path = model.export(format="onnx", imgsz=imgsz, opset=12, simplify=False)

    exported = Path(exported_path)
    target = MODELS_DIR / out_name
    exported.replace(target)
    print(f"Exported: {target}")


if __name__ == "__main__":
    export_one(PLATE_PT, "license_plate.onnx", imgsz=640)
    export_one(CHAR_PT, "character.onnx", imgsz=640)
    print("Done.")
