# Test Code (legacy)

Bring-up sketches used during hardware development. **Use [`firmware/biogen_ems/`](../firmware/biogen_ems/) for production.**

| Sketch | Purpose |
|--------|---------|
| `Blink/` | Board LED sanity check |
| `Test_Demux/` | Cycle D1–D4 demux lines |
| `Test_EMG/` | Early EMG serial experiment (STL-heavy; may not compile on nRF52) |

The `Test_Demux/sketch_jul11a/` duplicate was removed; it referenced an undefined LED bar library.
