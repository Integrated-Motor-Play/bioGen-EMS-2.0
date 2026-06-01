# Bill of Materials

Parts identified from the circuit design ([`Circuit Designs/bioGen-EMS-2.0.ckt`](../Circuit%20Designs/bioGen-EMS-2.0.ckt)) and CAD assembly (V2.2).

## Electronics

| Qty | Part | MPN / ID | Notes |
|-----|------|----------|-------|
| 1 | Seeed XIAO nRF52840 | — | Main MCU; USB serial + BLE |
| 1 | Seeed XIAO Expansion Board | — | Optional; matches V2.0 CAD |
| 4 | Adafruit STEMMA Relay | 4409 | Channel switching |
| 1 | SparkFun connector | PRT-13854 | Per circuit file |
| 1 | 4-channel demultiplexer | — | Select lines driven by D1–D4 |
| 1 | Grove EMG Detector | — | Muscle activity sensing on A0 |
| 1 | Off-the-shelf EMS/TENS unit | — | Stimulation source; switched by relays |
| — | Electrode pads & cables | — | For EMS output and EMG input |

## Enclosure (V2.2)

| Process | Files |
|---------|-------|
| Laser cut (acrylic) | `CAD Files/V2.2/Acrylic*.DXF` |
| 3D print | `CAD Files/V2.2/Top.STL`, `CAD Files/V2.2/Base.STL` |

See [enclosure.md](enclosure.md) for full file list.

## Tools

- Soldering iron, wire, breadboard or PCB
- Arduino IDE with Seeed nRF52 board package
- Laser cutter and/or 3D printer (for enclosure)

## Purchasing

- [Adafruit STEMMA Relay (4409)](https://www.adafruit.com/product/4409)
- [Seeed XIAO nRF52840](https://www.seeedstudio.com/XIAO-BLE-Sense-p-3721.html)
- [Grove EMG Detector](https://www.seeedstudio.com/Grove-EMG-Detector-p-1737.html)
