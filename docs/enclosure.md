# Enclosure (V2.2 — current)

Use **`CAD Files/V2.2/`** for new builds. Older revisions (V2.0, V2.1) are legacy references only.

## V2.2 manufacturing files

### Laser cut (acrylic)

| File | Purpose |
|------|---------|
| `Acrylic.DXF` | Main acrylic layout |
| `Acrylic_front_back.DXF` | Front/back panels |
| `Acrylic_side.DXF` | Side panels |
| `Acrylic_right_left.DXF` | Left/right panels |

### 3D print

| File | Purpose |
|------|---------|
| `Top.STL` | Top shell |
| `Base.STL` | Bottom shell |

### SolidWorks source

Assembly and parts: `BioGen_Box_Assembly.SLDASM`, `Top.SLDPRT`, `Base.SLDPRT`, `Front-Back.SLDPRT`, `Left-Right.SLDPRT`, `Board.SLDPRT`, `Speaker.SLDPRT`.

### CNC / other

- `BioGen_Box_Assembly.gcode` — machine-specific; verify settings before running on your printer/CNC.

## Legacy revisions

| Version | Folder | Notes |
|---------|--------|-------|
| V2.0 | `CAD Files/V2.0/` | Early burger-style stack; Seeed Xiao + STEMMA relay CAD |
| V2.1 | `CAD Files/V2.1/` | Panelized wood/acrylic drawings in `Drawings/` |
| V2.2 | `CAD Files/V2.2/` | **Current** — simplified acrylic, speaker cutout |

See [changelog-hardware.md](changelog-hardware.md) for differences.
