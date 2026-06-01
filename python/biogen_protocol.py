"""bioGen-EMS 2.0 command protocol (Auto-Paizo compatible)."""

from __future__ import annotations

CHANNEL_ON = {0: "E", 1: "A", 2: "B", 3: "C", 4: "D"}
CHANNEL_OFF = {0: "e", 1: "a", 2: "b", 3: "c", 4: "d"}
RESET_CMD = "r"

DEFAULT_BAUD = 115200


def channel_on(channel: int) -> str:
    if channel not in CHANNEL_ON:
        raise ValueError(f"channel must be 0-4, got {channel}")
    return CHANNEL_ON[channel]


def channel_off(channel: int) -> str:
    if channel not in CHANNEL_OFF:
        raise ValueError(f"channel must be 0-4, got {channel}")
    return CHANNEL_OFF[channel]


def reset_all() -> str:
    return RESET_CMD


def send_command(ser, cmd: str) -> None:
    """Send a single-character command over pyserial."""
    ser.write(cmd.encode("ascii"))
    ser.flush()
