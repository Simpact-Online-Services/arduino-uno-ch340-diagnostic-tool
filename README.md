# Arduino Uno Ch340 Diagnostic Tool
This Arduino sketch helps diagnose serial communication failures, bootloader issues, or USB instability in CH340G-based Arduino Uno clones. It uses LED patterns and timestamped serial messages to reveal whether the board is executing properly, resetting unexpectedly, or stuck in a loop. Ideal for debugging boards with problematic USB-B ports.

# Arduino Uno CH340 Diagnostic Tool

For those working with an Arduino Uno CH340 (CH340G or CH340C) and experiencing issues where the C++ program hangs or becomes unresponsive a few seconds after running — especially after uploading code via the USB-B port — this issue appears to be hardware-related. Specifically, it is likely tied to the CH340G or CH340C chip on the board, which can cause the program to freeze or repeatedly execute the same line of code. The following scenarios have been tested to isolate the issue:

- When the USB-B port was used for both power and serial communication (connected to a laptop), the program hung and stopped progressing after a few seconds.
- When the USB-B port was used only as a power source (connected to a USB power adapter), the same issue occurred — the board froze after a few seconds and repeatedly output the same serial line.
- When the board was powered using the power jack and the USB-B port was connected for serial communication, the issue persisted.
- A future test scenario involves powering the board through the power jack while using the USB-B port solely for serial communication — by disconnecting the USB power line and keeping only the data lines and ground connected — to see if the issue still occurs.

To diagnose this issue, the provided `main.cpp` sketch helps determine whether your board exhibits the same problem. The code blinks the onboard LED at preset intervals and prints the status of each iteration to the Serial Monitor. If the program hangs and the LED keeps blinking continuously while the same line is repeatedly printed to the serial output, you will see a warning message on the Serial Monitor. This behavior strongly indicates the presence of the CH340-related issue.

To work around this issue, I used a USB-to-TTL serial adapter to directly connect to the board. This way, after uploading the program to the board using the USB-B port, I disconnected the USB-B cable and powered the board via the power jack. I then used the USB-to-TTL adapter to retrieve serial output without encountering the same hanging or reset behavior. To do this, make sure the USB-to-TTL adapter is wired correctly: connect the ground (GND) to the board’s GND, the TX of the adapter to the RX pin of the board (Pin 0), and the RX of the adapter to the TX pin of the board (Pin 1). It is also crucial to match the baud rate in your Serial Monitor with the one defined in the sketch — in this case, 9600 baud — otherwise, you may see garbage or no output at all.

## Other Important Considerations

- When uploading code to the board, make sure the USB-to-TTL adapter is fully disconnected; otherwise, your IDE may not be able to establish a connection with the board.
- When uploading a sketch, ensure the Serial Monitor is closed, as leaving it open can interfere with the upload process and cause it to fail.
