# bioGen-EMS-2.0

**bioGen-EMS 2.0** is an open-source, programmable four-channel Electrical Muscle Stimulation (EMS) toolkit for HCI research, rehabilitation experiments, interactive installations, and body-actuating games.

It builds on [bioGen-EMS](https://github.com/Integrated-Motor-Play/bioGen-EMS) and works with [Auto-Paizo](https://github.com/Integrated-Motor-Play/Auto-Paizo) using a shared single-character control protocol over USB serial and BLE.

## Table of contents

- [Features](#features)
- [Circuit](#circuit)
- [Repository layout](#repository-layout)
- [Quick start](#quick-start)
- [Documentation](#documentation)
- [Hardware requirements](#hardware-requirements)
- [Safety](#safety)
- [Contributing](#contributing)
- [License](#license)

## Features

- **Four-channel relay control** via demultiplexer select lines (D1–D4)
- **Auto-Paizo compatible** commands (`A/a` … `D/d`, `E/e`, `r`) on serial and BLE
- **EMG telemetry** over BLE (Grove EMG on A0)
- **Production firmware** for Seeed XIAO nRF52840
- **Python CLI** for bench testing without Unity
- **Open-source** hardware CAD, circuit, and firmware (MIT)

## Circuit

![bioGen-EMS-2.0 Circuit](https://user-images.githubusercontent.com/91541296/176067417-406898d9-ad55-4183-bad4-2f2903ceec28.png)

Schematic: [`Circuit Designs/bioGen-EMS-2.0.ckt`](Circuit%20Designs/bioGen-EMS-2.0.ckt) (open in Cirkit Studio)

## Repository layout

```
bioGen-EMS-2.0/
├── firmware/biogen_ems/    # Production sketch (Seeed XIAO nRF52840)
├── python/                 # Serial control CLI
├── examples/               # Example scripts
├── docs/                   # BOM, assembly, safety, protocol, enclosure
├── hardware/               # Hardware documentation index
├── CAD Files/              # Enclosure V2.0–V2.2 (use V2.2)
├── Circuit Designs/
└── Test Code/              # Legacy bring-up sketches (deprecated)
```

## Quick start

### 1. Clone and install Python dependencies

```bash
git clone https://github.com/Integrated-Motor-Play/bioGen-EMS-2.0.git
cd bioGen-EMS-2.0
pip install -r python/requirements.txt
```

### 2. Flash firmware

1. Install the [Seeed nRF52 board package](https://wiki.seeedstudio.com/XIAO_BLE/) in Arduino IDE.
2. Install the **ArduinoBLE** library from Library Manager.
3. Open [`firmware/biogen_ems/biogen_ems.ino`](firmware/biogen_ems/biogen_ems.ino).
4. Select **Seeed XIAO nRF52840** and upload.

See [firmware/README.md](firmware/README.md) for the smoke-test checklist.

### 3. Control over USB serial

```bash
# List available serial ports
python python/ems_control.py --list-ports

# Pulse channel 1 for 500 ms (auto-selects first port if --port omitted)
python python/ems_control.py --port /dev/cu.usbmodem101 --pulse 1 --duration 500

# Turn channel 2 on / off
python python/ems_control.py --port /dev/cu.usbmodem101 --channel 2 --on
python python/ems_control.py --port /dev/cu.usbmodem101 --channel 2 --off

# Reset all channels
python python/ems_control.py --port /dev/cu.usbmodem101 --reset
```

On Windows, use `COM3` (or your port) instead of `/dev/cu.usbmodem101`.

Example script: [`examples/basic_stim.py`](examples/basic_stim.py)

### 4. Build the hardware

1. [Bill of materials](docs/bom.md)
2. [Assembly guide](docs/assembly.md)
3. [Enclosure V2.2](docs/enclosure.md) — laser-cut acrylic + 3D-printed top/base

### 5. Use with Auto-Paizo

Pair over BLE and run calibration before participant sessions. See [docs/auto-paizo.md](docs/auto-paizo.md).

## Documentation

| Document | Description |
|----------|-------------|
| [docs/bom.md](docs/bom.md) | Bill of materials |
| [docs/pinout.md](docs/pinout.md) | MCU pin mapping |
| [docs/protocol.md](docs/protocol.md) | Serial and BLE command reference |
| [docs/assembly.md](docs/assembly.md) | Build order and wiring |
| [docs/safety.md](docs/safety.md) | Safety and ethics guidelines |
| [docs/enclosure.md](docs/enclosure.md) | V2.2 enclosure manufacturing files |
| [docs/changelog-hardware.md](docs/changelog-hardware.md) | Enclosure revision history |
| [docs/auto-paizo.md](docs/auto-paizo.md) | Unity / Auto-Paizo integration |
| [hardware/README.md](hardware/README.md) | Hardware doc index |
| [CAD Files/README.md](CAD%20Files/README.md) | CAD file index |

## Hardware requirements

| Component | Notes |
|-----------|--------|
| Seeed XIAO nRF52840 | Main controller |
| 4× Adafruit STEMMA Relay (4409) | Per-channel switching |
| 4-channel demux | Select lines on D1–D4 |
| Off-the-shelf EMS/TENS unit | Stimulation source (switched by relays) |
| Grove EMG Detector | Optional; muscle activity on A0 |
| Electrodes and cables | Per EMS unit manufacturer |

## Safety

EMS affects the human body. Read [docs/safety.md](docs/safety.md) before building or running studies. Use ethics approval, informed consent, conservative intensity, and never test on participants without proper calibration and supervision.

## Contributing

1. Fork the repository.
2. Create a branch: `git checkout -b feature/your-feature`
3. Commit your changes and open a pull request.

## License

MIT — see [LICENSE](LICENSE).

## Contact

hello@rakeshpatibanda.com
