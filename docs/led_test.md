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

---

# 🖥️ Extended Test — Serial Control

## Objective

Extend the basic LED test by adding serial communication, allowing the LED to be controlled through user input.

---

## Code

```cpp
#define LED_PIN 25

void ligarLED() {
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED LIGADO");
}

void desligarLED() {
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED DESLIGADO");
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("Sistema iniciado");
}

void loop() {
  if (Serial.available()) {
    char comando = Serial.read();

    if (comando == '1') {
      ligarLED();
    }

    if (comando == '0') {
      desligarLED();
    }
  }
}
```

---

## Expected Behavior

* Sending `1` → LED ON
* Sending `0` → LED OFF
* Serial Monitor prints system status

---

## Results

The system correctly responded to all commands sent via Serial Monitor.

---

## 📷 Note

No image was recorded for this test. This will be added in future updates.

---

## Conclusion

This extension demonstrates that the system can:

* Receive external input
* Process commands in real time
* Control outputs dynamically

This is a key step toward more advanced features such as telemetry and remote control.

