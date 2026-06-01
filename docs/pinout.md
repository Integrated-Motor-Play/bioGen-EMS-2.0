# Pinout (Seeed XIAO nRF52840)

Production firmware: [`firmware/biogen_ems/`](../firmware/biogen_ems/).

## Demux select lines (channels 1–4)

| Signal | XIAO pin | Arduino define | Channel |
|--------|----------|----------------|---------|
| SEL_A | D1 | `PIN_SEL_A` (1) | 1 |
| SEL_B | D2 | `PIN_SEL_B` (2) | 2 |
| SEL_C | D3 | `PIN_SEL_C` (3) | 3 |
| SEL_D | D4 | `PIN_SEL_D` (4) | 4 |

Each channel is selected by driving one select line HIGH and the others LOW. Reset (`r`) drives all select lines LOW.

Validated in [`Test Code/Test_Demux/Test_Demux.ino`](../Test%20Code/Test_Demux/Test_Demux.ino).

## EMG sensor

| Signal | Pin | Notes |
|--------|-----|-------|
| EMG analog | A0 | Production firmware (`EMG_PIN`) |
| EMG analog (legacy test) | A7 | Used in early `sketch_jul11a` demo only |

Connect the Grove EMG Detector to the analog input per Grove wiring (typically A0 on XIAO).

## Channel 0 (protocol `E` / `e`)

Auto-Paizo uses channel 0 for some game mappings. With a 4-line demux, channel 0 is implemented as **all select lines LOW** (no channel selected). `E` enables that idle state; `e` is equivalent to off.

## Built-in LED

`LED_BUILTIN` may toggle on channel activity for debugging (optional in firmware).
