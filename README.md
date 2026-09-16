# RoboSumo Autonomous Robot

Autonomous RoboSumo robot developed as part of my first-year engineering coursework at Technological University Dublin.

The robot uses an Arduino Nano, two TCRT5000 infrared sensors and PWM motor control to navigate the arena using a finite-state-machine control system.

## My Contribution

My main responsibility was developing the final control architecture and Arduino C++ code.

I also contributed to:

- chassis design and laser cutting
- soldering and sensor integration
- electrical wiring
- physical testing and debugging
- sensor threshold and motor timing calibration

## Hardware

- Arduino Nano
- SN754410NE motor driver
- 2 × TCRT5000 IR sensors
- DC motors
- Breadboard electronics
- 6 V battery system
- Laser-cut 3 mm plywood chassis

## Control System

The final program uses a finite-state machine with more than 15 states.

The robot can:

- detect the arena boundary using downward-facing IR sensors
- reverse and realign after reaching an edge
- follow and reacquire the boundary
- independently control left and right motor speeds using PWM
- perform timed turns toward the centre
- recover from unexpected sensor conditions
- stop near the centre of the arena

Testing on the physical arena exposed issues that were not obvious during initial development, including false sensor behaviour near the raised platform edge and differences between the two motors.

The control logic was iteratively adjusted through repeated testing, including changes to sensor thresholds, PWM values, timing and recovery states.

## Result

The completed robot won its first four consecutive tournament matches.

## Code

The final Arduino control program is available here:

[`RoboSumo.ino`](RoboSumo.ino)

## Development Blog

The original project development log is available on the TU Dublin RoboSumo site:

https://robosumo.eu/mainman/view.php?mdfile=20251204_163552.md
