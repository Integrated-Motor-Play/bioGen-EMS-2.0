# Firmware

Production sketch: [`biogen_ems/biogen_ems.ino`](biogen_ems/biogen_ems.ino)

**Target board:** Seeed XIAO nRF52840 (Sense or non-Sense)

## Setup (Arduino IDE)

1. Install [Arduino IDE](https://www.arduino.cc/en/software) 2.x.
2. Add board package: **Seeed nRF52 Boards** via Board Manager (`https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json`).
3. Install library: **ArduinoBLE** (Library Manager).
4. Open `biogen_ems/biogen_ems.ino`.
5. Select **Seeed XIAO nRF52840** → upload.

## Configuration

Edit [`biogen_ems/config.h`](biogen_ems/config.h):

| Define | Default | Purpose |
|--------|---------|---------|
| `PIN_SEL_A`–`D` | 1–4 | Demux select lines |
| `EMG_PIN` | A0 | Grove EMG analog input |
| `EMG_DEBUG_SERIAL` | 0 | Set `1` for CSV on Serial |
| `BLE_DEVICE_NAME` | BioGen-EMS | BLE advertised name |

## Smoke test checklist

Perform **without electrodes on a participant**.

### 1. Serial connection

1. Connect XIAO via USB; note the serial port (e.g. `/dev/cu.usbmodem*` on macOS).
2. Open Serial Monitor at **115200** baud.
3. Confirm boot message: `bioGen-EMS ready`.

### 2. Channel commands

Send one character per line (no intensity control):

| Send | Expected |
|------|----------|
| `A` | Channel 1 ON (D1 HIGH, D2–D4 LOW) |
| `a` | Channel 1 OFF |
| `B` | Channel 2 ON |
| `r` | All channels OFF |

Verify with a multimeter or LED on demux lines if relays are not yet wired.

### 3. Python CLI

```bash
pip install -r python/requirements.txt
python python/ems_control.py --list-ports
python python/ems_control.py --port /dev/cu.usbmodemXXXX --pulse 1 --duration 500
python python/ems_control.py --port /dev/cu.usbmodemXXXX --reset
```

### 4. BLE (optional)

1. Scan for **BioGen-EMS** from a phone or nRF Connect.
2. Connect to service `19B10000-E8F2-537E-4F6C-D104768A1214`.
3. Write `0x42` (`B`) to characteristic `19B10001-...` → channel 2 ON.
4. Subscribe to EMG characteristic `19B10002-...` for int32 notifications.

### 5. Auto-Paizo

Flash this firmware, then follow [docs/auto-paizo.md](../docs/auto-paizo.md).

## Troubleshooting

| Issue | Check |
|-------|-------|
| BLE init failed | Board package and ArduinoBLE installed |
| No serial port | USB cable supports data; driver for J-Link/USB |
| Wrong channel | [docs/pinout.md](../docs/pinout.md) wiring vs `config.h` |
| EMG flatline | Grove EMG on A0; sensor powered |

## Legacy tests

Bring-up sketches in [`Test Code/`](../Test%20Code/) are deprecated; use this firmware instead.
