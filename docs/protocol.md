# Control Protocol

bioGen-EMS 2.0 uses the same single-character command set as [Auto-Paizo](https://github.com/Integrated-Motor-Play/Auto-Paizo). Commands are one ASCII character; an optional trailing newline (`\n`) is accepted.

## Channel commands

| Command | Channel | Action |
|---------|---------|--------|
| `A` | 1 | ON |
| `a` | 1 | OFF |
| `B` | 2 | ON |
| `b` | 2 | OFF |
| `C` | 3 | ON |
| `c` | 3 | OFF |
| `D` | 4 | ON |
| `d` | 4 | OFF |
| `E` | 0 | ON (all demux lines low / idle) |
| `e` | 0 | OFF |
| `r` | — | Reset all channels OFF |

There is **no intensity command** in this protocol. Stimulation strength is set on the external EMS unit; the controller only selects which channel is active.

## USB serial

- Baud rate: **115200**
- Send one character per command, e.g. `A` or `A\n`
- EMG debug CSV (when enabled): `raw,filtered,level` per line at 10 ms interval

## BLE GATT (Auto-Paizo compatible)

| Role | UUID |
|------|------|
| Service | `19B10000-E8F2-537E-4F6C-D104768A1214` |
| Command (write) | `19B10001-E8F2-537E-4F6C-D104768A1214` |
| EMG (notify) | `19B10002-E8F2-537E-4F6C-D104768A1214` |

- Write a single command byte to the command characteristic.
- EMG level is sent as a **32-bit signed integer** (little-endian) on notify.

## Example session (serial)

```text
A    # channel 1 ON
a    # channel 1 OFF
B    # channel 2 ON
r    # all OFF
```

## Python

See [`python/ems_control.py`](../python/ems_control.py) and [`python/biogen_protocol.py`](../python/biogen_protocol.py).
