# Assembly Guide

Build order for bioGen-EMS 2.0.

## 1. Review the circuit

1. Open [`Circuit Designs/bioGen-EMS-2.0.ckt`](../Circuit%20Designs/bioGen-EMS-2.0.ckt) in Cirkit Studio (or export the schematic image from the README).
2. Confirm parts against [bom.md](bom.md).

## 2. Wire the electronics

1. Mount the Seeed XIAO nRF52840 (and expansion board if used).
2. Connect demux select lines to **D1–D4** per [pinout.md](pinout.md).
3. Wire four STEMMA relays for channel switching to the EMS unit outputs.
4. Connect the Grove EMG detector to **A0**.
5. Double-check power, ground, and relay common paths before powering the EMS unit.

## 3. Flash firmware

1. Install the Seeed nRF52 board package in Arduino IDE.
2. Open [`firmware/biogen_ems/biogen_ems.ino`](../firmware/biogen_ems/biogen_ems.ino).
3. Select board **Seeed XIAO nRF52840** and upload.
4. Run serial smoke tests from [firmware/README.md](../firmware/README.md).

## 4. Build the enclosure

Follow [enclosure.md](enclosure.md) for V2.2 laser-cut and 3D-printed parts.

## 5. Pre-use checks

1. **Without electrodes on a participant**: send `A`, then `a`, then `r` over serial; verify only one channel selects at a time.
2. Set EMS unit intensity to minimum before first attached test.
3. Read [safety.md](safety.md) and complete ethics/calibration steps for research use.

## 6. Software integration

- **Python CLI**: [`python/ems_control.py`](../python/ems_control.py)
- **Auto-Paizo**: [auto-paizo.md](auto-paizo.md)
