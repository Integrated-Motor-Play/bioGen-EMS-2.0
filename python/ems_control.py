#!/usr/bin/env python3
"""CLI for bioGen-EMS 2.0 over USB serial."""

from __future__ import annotations

import argparse
import sys
import time
from pathlib import Path

# Support running from repo root: python python/ems_control.py
sys.path.insert(0, str(Path(__file__).resolve().parent))

try:
    import serial
    import serial.tools.list_ports
except ImportError:
    print("Install dependencies: pip install -r python/requirements.txt", file=sys.stderr)
    sys.exit(1)

from biogen_protocol import (
    DEFAULT_BAUD,
    channel_off,
    channel_on,
    reset_all,
    send_command,
)


def list_ports() -> None:
    ports = serial.tools.list_ports.comports()
    if not ports:
        print("No serial ports found.")
        return
    for p in ports:
        print(f"  {p.device}\t{p.description}")


def open_port(port: str | None, baud: int) -> serial.Serial:
    if port is None:
        ports = list(serial.tools.list_ports.comports())
        if not ports:
            raise SystemExit("No serial port found. Use --list-ports or --port.")
        port = ports[0].device
        print(f"Using port {port}", file=sys.stderr)
    return serial.Serial(port, baud, timeout=1)


def monitor_emg(ser: serial.Serial) -> None:
    print("Monitoring EMG CSV (Ctrl+C to stop). Enable EMG_DEBUG_SERIAL in firmware.")
    try:
        while True:
            line = ser.readline().decode("utf-8", errors="replace").strip()
            if line:
                print(line)
    except KeyboardInterrupt:
        print("\nStopped.")


def main() -> None:
    parser = argparse.ArgumentParser(description="bioGen-EMS 2.0 serial control")
    parser.add_argument("--list-ports", action="store_true", help="List serial ports")
    parser.add_argument("--port", "-p", help="Serial port path")
    parser.add_argument("--baud", type=int, default=DEFAULT_BAUD)
    parser.add_argument("--channel", "-c", type=int, choices=[0, 1, 2, 3, 4])
    parser.add_argument("--on", action="store_true", help="Turn channel on")
    parser.add_argument("--off", action="store_true", help="Turn channel off")
    parser.add_argument("--pulse", action="store_true", help="Pulse channel on then off")
    parser.add_argument("--duration", type=int, default=500, help="Pulse duration ms")
    parser.add_argument("--reset", action="store_true", help="Reset all channels")
    parser.add_argument("--monitor-emg", action="store_true", help="Read EMG debug CSV")
    args = parser.parse_args()

    if args.list_ports:
        list_ports()
        return

    if args.monitor_emg:
        with open_port(args.port, args.baud) as ser:
            monitor_emg(ser)
        return

    if args.reset:
        with open_port(args.port, args.baud) as ser:
            send_command(ser, reset_all())
            print("Reset all channels.")
        return

    if args.channel is not None:
        with open_port(args.port, args.baud) as ser:
            if args.pulse:
                send_command(ser, channel_on(args.channel))
                time.sleep(args.duration / 1000.0)
                send_command(ser, channel_off(args.channel))
                print(f"Pulsed channel {args.channel} for {args.duration} ms.")
            elif args.on:
                send_command(ser, channel_on(args.channel))
                print(f"Channel {args.channel} ON.")
            elif args.off:
                send_command(ser, channel_off(args.channel))
                print(f"Channel {args.channel} OFF.")
            else:
                parser.error("Specify --on, --off, or --pulse with --channel")
        return

    parser.print_help()


if __name__ == "__main__":
    main()
