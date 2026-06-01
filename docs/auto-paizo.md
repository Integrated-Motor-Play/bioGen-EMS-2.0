# Auto-Paizo Integration

[bioGen-EMS 2.0](https://github.com/Integrated-Motor-Play/bioGen-EMS-2.0) is designed to work with [Auto-Paizo](https://github.com/Integrated-Motor-Play/Auto-Paizo), a Unity project for body-actuating play research.

## Requirements

- Seeed XIAO nRF52840 flashed with [`firmware/biogen_ems/biogen_ems.ino`](../firmware/biogen_ems/biogen_ems.ino)
- Windows or macOS with Bluetooth LE
- Auto-Paizo built from source (see Auto-Paizo README)

## Pairing

1. Power the controller; do **not** attach electrodes to a participant yet.
2. Put the XIAO in range; ensure firmware BLE is advertising (device name: `BioGen-EMS`).
3. Pair from the OS Bluetooth settings if required by your platform.
4. In Auto-Paizo, open the Bluetooth Connect scene and select the device via `BluetoothConnector`.

## Protocol

Auto-Paizo sends the same single-character commands documented in [protocol.md](protocol.md) to the BLE command characteristic.

EMG calibration uses the EMG characteristic notify stream (32-bit integer level).

## Calibration

Use in-app panels before participant play:

- `EMGCalibrationPanel`
- `EMGSensitivitySlider`

Hold the target muscle steady during baseline capture (see Grove EMG notes in firmware README).

## Safety

Follow [safety.md](safety.md) and your ethics protocol. Auto-Paizo documentation also lists conservative intensity and participant communication practices.

## Differences from bioGen-EMS 1.0

| | v1 | v2 |
|---|----|----|
| MCU | Adafruit Feather 32u4 Bluefruit LE | Seeed XIAO nRF52840 |
| Transport | Classic Bluetooth serial | BLE GATT + USB serial |
| Enclosure | Burger v1 STL | V2.2 box |
| Commands | Same `A/a`…`D/d`, `E/e`, `r` | Same |
