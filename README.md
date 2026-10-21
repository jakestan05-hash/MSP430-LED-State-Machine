# MSP430 LED Control System

An interrupt-driven LED control system developed for **ELEC 325 – Embedded Systems** at Campbell University (April 2026).

**Author:** Jake Stanley  
**Target microcontroller:** Texas Instruments MSP430FR2355  
**Development environment:** Texas Instruments Code Composer Studio (CCS)

## Overview

This project controls five LEDs using three push buttons and a four-state finite state machine. It demonstrates GPIO configuration, interrupt service routines, timer-driven timing, and modular embedded C programming.

## Operating modes

| Mode | Behavior |
| --- | --- |
| OFF | Turns all LEDs off. |
| SPEED | Cycles through the LEDs. Right button reduces the update interval; left button increases it. |
| DIRECTION | Moves an illuminated LED along the row in response to the left/right buttons. |
| COUNTER | Uses the LEDs to represent an incrementing/decrementing count with an animated transition. |

The mode button advances through the four states and wraps back to OFF.

## Hardware pin assignments

| Signal | MSP430 pin | Source |
| --- | --- | --- |
| LED 1–5 | P6.0–P6.4 | `led_LedServices.c` |
| Mode button | P1.1 | `btn_ButtonServices.c` |
| Right button | P2.3 | `btn_ButtonServices.c` |
| Left button | P4.1 | `btn_ButtonServices.c` |

The button inputs use internal pull-up resistors and falling-edge GPIO interrupts. Physical wiring and any external LED current-limiting components must be checked against the actual board and circuit before assembly.

## Firmware architecture

| File | Responsibility |
| --- | --- |
| `main.c` | Startup initialization and main scheduler loop |
| `sm_StateMachine.c/.h` | Operating modes and state transitions |
| `btn_ButtonServices.c/.h` | Button GPIO configuration and interrupt handlers |
| `led_LedServices.c/.h` | LED configuration and control |
| `tmr_TimerB.c/.h` | Timer_B setup and periodic tick interrupt |
| `common.h` | Shared types and macros |

Timer_B0 generates a periodic tick intended to be approximately **10 ms** under the project's clock assumptions. Mode timing is based on this tick; actual tick duration depends on the configured SMCLK frequency.

## Build and run

1. Install Texas Instruments Code Composer Studio with MSP430 device/compiler support.
2. Import the directory containing `.project`, `.cproject`, and `.ccsproject` as an existing CCS project.
3. Select or verify the MSP430FR2355 target and your debugger configuration.
4. Build, flash, and debug on the intended hardware.

**Note:** This is an archived classroom project. The included CCS configuration originated in a specific local installation and may need toolchain, device package, or project-path adjustments on another computer. The repository has **not** been rebuilt or hardware-tested as part of this packaging step.

## Repository contents

The original CCS project files and source organization are retained to make importing easier. `Debug/` and editor caches are excluded. The bundled `driverlib/` sources are Texas Instruments code and retain their original copyright and redistribution notices.

## Attribution

Application project by Jake Stanley (2026). Bundled Texas Instruments DriverLib files are third-party material under the notices included in their source files.
