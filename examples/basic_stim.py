#!/usr/bin/env python3
"""Pulse channel 1 for 500 ms — minimal bioGen-EMS example."""

import sys
import time
from pathlib import Path

# Allow import from python/
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "python"))

import serial
from biogen_protocol import DEFAULT_BAUD, channel_off, channel_on, send_command


def main() -> None:
    port = sys.argv[1] if len(sys.argv) > 1 else None
    if port is None:
        import serial.tools.list_ports

        ports = list(serial.tools.list_ports.comports())
        if not ports:
            raise SystemExit("No serial port. Usage: basic_stim.py [/dev/cu.usbmodemXXX]")
        port = ports[0].device
        print(f"Using {port}")

    with serial.Serial(port, DEFAULT_BAUD, timeout=1) as ser:
        send_command(ser, channel_on(1))
        time.sleep(0.5)
        send_command(ser, channel_off(1))
    print("Done: channel 1 pulse 500 ms")


if __name__ == "__main__":
    main()
