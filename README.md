# Low-Altitude Rocket Observation System

A model rocket with a custom flight computer that records altitude, acceleration and rotation data on a microSD card and runs a state machine intended to trigger a parachute release. Developed as a hands-on project combining software, electronics and physics.

📄 **Full report:** see `docs/` (Low-Altitude_Rocket.pdf)

## Overview

- **Flight computer:** ESP32 with a BMP280 barometer and an MPU6050 accelerometer/gyroscope
- **Data logging:** one CSV row per sample (up to 20 Hz) written to a microSD card
- **Flight software:** finite state machine with four states (0 Pad, 1 Ascent, 2 Ejection, 3 Descent)
- **Recovery:** a nichrome wire, switched by a MOSFET, burns the line that holds the parachute compartment closed
- **Rocket:** about 310 g, Estes C6-3 motor, cardboard airframe with self-made plastic fins

## Status

Version 1 was built, bench-tested and flown three times. The data logging worked in all three flights. The state machine never left State 0 in flight, because the barometer (as configured) was too slow to detect such short flights (1 to 3 s), so the parachute ejection was never triggered in flight. The electronic part of the recovery sequence was validated on the bench; the nose-cone separation was not.

Planned for Version 2: detecting lift-off from the acceleration, a timer as backup, a faster barometer configuration, better mass distribution and stability, and a redesigned ejection mechanism (for example, a servomotor opening the parachute compartment).

## Hardware

| Component | Function |
|---|---|
| ESP32 | Reads sensors, runs the state machine, logs data |
| BMP280 | Barometric pressure / relative altitude |
| MPU6050 | 3-axis accelerometer and gyroscope |
| microSD module | Stores the flight log (CSV) |
| 800 mAh LiPo | Powers the ESP32 and peripherals |
| 600 mAh LiPo | Powers only the nichrome wire |
| IRLZ44N MOSFET + nichrome wire | Burns the line that releases the parachute |
| LEDs, buzzer, reset button | Status indication and restart without opening the rocket |

## Software

Written in C++ with the Arduino framework (Arduino IDE), using the `Adafruit_Sensor`, `Adafruit_BMP280` and `Adafruit_MPU6050` libraries.

## Repository structure

- `firmware/` — flight software (state machine, sensor reading, logging)
- `firmware/tests/` — test sketches for each component
- `data/` — logs of the three flight tests
- `docs/` — project report
- `photos/` — photos of the build process

## Flight data

| File | Description |
|---|---|
| `flight_realtest1_log_PROJETO.xlsx` | Flight Test 1 (no launch rod) |
| `flight_realtest2_log.csv` | Flight Test 2 (semicolon-separated) |
| `flight_realtest3_log.csv` | Flight Test 3 (comma-separated) |

Columns: time (ms), state, relative altitude (m), acceleration x/y/z (m/s²), angular rate x/y/z (rad/s).

## Author

Inês Lage Marchante: BSc in Computer Engineering
