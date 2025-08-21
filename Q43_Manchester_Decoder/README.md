# Manchester Decoder using CLC modules and UART protocol in PIC18F27Q43

## Overview
This project implements a **Manchester decoder** on the PIC18F27Q43 using its **Configurable Logic Cells (CLC)** and **Numerically Controlled Oscillator (NCO)** peripherals.  
The decoder extracts serial data from a Manchester-encoded input signal and passes it to **UART5** for further processing and storing.

## Hardware Setup
- **Input (Manchester signal):** RC3  
- **Decoded Output:** RC7  
- **UART Input:** RA5 (configured as `UART5RX`)  
- RC7 is connected to RA5 through a **series resistor** to filter unwanted spikes.


## Firmware Notes
- Decoder logic runs entirely in hardware using **CLC** and **NCO**.  
- Firmware is only used for **initializing peripherals** and configuring **UART5**.  
- The CPU remains free to handle other application logic.  

---

## Theory (Background)

Manchester encoding is a line coding method where each bit contains a mid-bit transition.  
- In the **G.E. Thomas format** (used here):  
  - `0 = low → high transition`  
  - `1 = high → low transition`  
- Each bit guarantees a transition, enabling reliable **clock recovery** and eliminating DC bias.  

In this decoder design:  
- A **CLC XOR gate** detects mid-bit transitions.  
- The **NCO**, triggered by these transitions, generates a precise **¾ bit-time pulse** for sampling.  
- A **CLC D-flip-flop** latches the incoming bit at the correct instant, producing clean decoded data.  
- The recovered **serial data** is then fed into **UART5** for further handling.  

This hardware-driven approach requires **minimal CPU cycles**, unlike software-only decoders, making it efficient and low-power.  

  
