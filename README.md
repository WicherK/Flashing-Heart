
# Flashing Heart

My first embedded project built with a pure ATtiny85 microcontroller and C++.

You can check how it works here:
https://www.youtube.com/watch?v=_E9moM0vMBc

## Description

Flashing Heart is a simple LED heart powered by an ATtiny85 and four 74HC595 shift registers. The project controls 30 LEDs while using only three microcontroller pins for data transmission.

The heart features multiple animation modes that can be switched using a push button:

- Static mode (all LEDs ON)
- Blinking heart
- Rotating single LED animation
- Heartbeat effect

The device is powered directly from a USB-C connector and was designed as a learning project to understand ATtiny85 programming and how it would be to control 30 leds with only 3 pins.

## Hardware

### Components

- ATtiny85
- 4 × 74HC595 shift registers
- 30 × Red LEDs
- USB-C power connector
- Push button
- 30 x 470Ω resistors
- 1 x capacitor for supply filtering 35V 220µF

### Connections

The ATtiny85 communicates with all shift registers using only three pins:

| ATtiny85 | 74HC595 |
|-----------|----------|
| PB0 | DATA (SER) |
| PB1 | LATCH (RCLK) |
| PB2 | CLOCK (SRCLK) |

## Software

The firmware is written in C++ using the Arduino framework for ATtiny85.

To upload the software I used my old arduino as ISP.

## Photos

I didn't create custom PCB for this project so I had to solder everything by hand.

![Flashing Heart](https://i.imgur.com/DV8nVPC.jpeg)
