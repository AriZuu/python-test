This is a simple test application for Pico]OS [micropython][1] port.
It runs on Texas Instruments MSP432 launchpad (using uart console) and
PIC32 chips.

PIC32 port is preliminary, I don't have real hardware (yet)
so it has been tested only under MPLAB X simulator.

You'll be needing following modules in parallel to this to build:

- picoos
- picoos-micro
- picoos-python
- micropython

For MSP432 (Cortex-M4) you'll need also:
- cmsis-ports

Working python is also required for build host.

[1]: http://micropython.org/
