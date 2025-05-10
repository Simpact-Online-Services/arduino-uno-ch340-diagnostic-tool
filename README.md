# Arduino Uno CH340 Diagnostic Tool

This repository provides a diagnostic sketch to help identify **serial communication failures**, **bootloader instability**, or **USB-related execution issues** in Arduino Uno clones that use the **CH340G or CH340C USB-to-serial chips**. These issues often result in the board freezing, rebooting, or repeatedly executing a single line of code.

Ideal for diagnosing unstable boards with **problematic USB-B ports**, this tool uses a combination of LED patterns and timestamped serial output to visually and textually confirm whether your board is functioning normally.

---

## Problem Overview

Many users working with **CH340G/CH340C-based Arduino Uno boards** encounter problems where the program:

- Freezes a few seconds after upload
- Repeats the same output in the serial monitor
- Shows continuous LED blinking but no functional loop progression

This behavior is usually linked to **hardware-level faults in the CH340 chip circuitry**, especially how it handles power or serial line interference.

---

## Tested Scenarios

| # | Power Source      | USB-B Connected | Serial Output Method | Result                                                           |
|---|-------------------|------------------|-----------------------|------------------------------------------------------------------|
| 1 | USB-B (laptop)    | Yes              | USB-B                 | Program hangs and repeatedly prints the same line               |
| 2 | USB-B (adapter)   | Yes (power only) | None                  | Same issue — board freezes after a few seconds                  |
| 3 | Power jack        | Yes              | USB-B                 | Issue persists — same stuck behavior                            |
| 4 | Power jack        | Planned test     | USB-B (data only)     | To test if removing USB power while keeping data solves issue   |


1. **USB-B used for both power and serial** (connected to a laptop): the board hangs and repeatedly outputs the same serial message.
2. **USB-B used only for power** (connected to a wall adapter): same hanging behavior occurred.
3. **Board powered via the DC jack** while USB-B was connected for serial: issue persisted.
4. **(Planned)**: Power via the DC jack and use USB-B *only for data* (disconnect 5V line) — to isolate whether the USB power line causes the fault.

---

## Diagnostic Method

Use the provided `main.cpp` sketch to test your board:

- Blinks the onboard LED at set intervals
- Prints each loop iteration with a millisecond timestamp
- Detects and warns if the loop is running too fast (indicating a reset or stuck loop)

If you observe the LED blinking in a fixed pattern while the same serial line is printed repeatedly — along with a **"WARNING: Loop running too fast - possible reset/stuck?"** message — your board is likely affected by the CH340-related issue.

---

## Workaround Using USB-to-TTL Adapter

To bypass the problematic CH340 chip, follow this workaround:

1. Upload the program normally via the USB-B port.
2. Disconnect the USB-B cable.
3. Power the board through the **power jack** (recommended).
4. Connect a **USB-to-TTL adapter** for serial output.

### Wiring Guide

| TTL Adapter Pin | Arduino Uno Pin |
|-----------------|-----------------|
| GND             | GND             |
| TX              | RX (Pin 0)      |
| RX              | TX (Pin 1)      |

- **Set the baud rate to `9600`** in the Serial Monitor (matches the sketch).

---

## Other Important Considerations

- **Disconnect the USB-to-TTL adapter** when uploading code — otherwise, your IDE may not connect to the board.
- **Close the Serial Monitor** before uploading a sketch — having it open can block the upload process and cause failures.

---

This tool is a lightweight and practical way to identify CH340-related board instability and serves as a quick validation for hardware troubleshooting.
