# 🔴 LED Test

## Objective

The goal of this test is to verify that the microcontroller (Arduino/ESP32) is correctly set up and capable of controlling a basic output component (LED).

---
<p align="center">
  <img src="images/led_setup.jpg" height="250">
  &nbsp;&nbsp;&nbsp;
  <img src="images/led_setup2.jpg" height="250">
</p>

## Setup

* Microcontroller: ESP32 / Arduino
* Component: LED
* Resistor: 220Ω
* Connection:

  * LED positive → GPIO pin
  * LED negative → GND (through resistor)

---

## Code

```cpp
#define LED 25
void setup() {
  pinMode(LED, OUTPUT);

}

void loop() {
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(1000);

}
```

---

## Expected Behavior

The LED should blink:

* ON for 1 second
* OFF for 1 second

---

## Result

The LED blinked as expected, confirming that:

* The microcontroller is functioning correctly
* GPIO output control is working
* The development environment is properly configured

---

## Conclusion

This basic test validates the foundation of the system. Future steps will include:

* Input handling
* Sensor integration
* Data collection
