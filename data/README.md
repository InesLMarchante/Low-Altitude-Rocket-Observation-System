# Data

Logs recorded on the microSD card during the tests. Time is measured in milliseconds since power-on.

| File | Description |
|---|---|
| `flight_parachute_test1_log.xlsx` | Bench test of the recovery sequence (rocket raised by hand) |
| `flight_realtest1_log.xlsx` | Flight Test 1 (no launch rod; ignition at about 164 s) |
| `flight_realtest2_log.xlsx` | Flight Test 2 (launch rod; ground reference taken with the rocket in the hand; ignition at about 362 s) |
| `flight_realtest3_log.xlsx` | Flight Test 3 (launch rod; ground reference taken on the platform; ignition at about 189 s) |

## Columns

| Column | Description |
|---|---|
| `Time(ms)` | Time since power-on (ms) |
| `State` | Flight state of the state machine (0 Pad, 1 Ascent, 2 Ejection, 3 Descent) |
| `Altitude(m)` | Barometric altitude relative to the ground reference taken at start-up (m) |
| `Accel_X`, `Accel_Y`, `Accel_Z` | Acceleration (m/s²) |
| `Gyro_X`, `Gyro_Y`, `Gyro_Z` | Angular rate (rad/s) |

The accelerometer is configured for ±16 g and the gyroscope for ±500 °/s (about 8.73 rad/s). 

#### See the report for the analysis of each test!
