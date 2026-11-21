#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_MPU6050.h>

// Instantiate sensors
Adafruit_BMP280 bmp;
Adafruit_MPU6050 mpu;

// Pin Definitions
const int CS_PIN = 5;
const int MOSFET_PIN = 25;
const int BUZZER_PIN = 15;
const int BUTTON_PIN = 32;

// LED Pins
const int RED_LED_PIN = 12;
const int GREEN_LED_PIN = 13;
const int BLUE_LED_PIN = 14;

// Finite State Machine (FSM) Variables
int flightState = 0; // 0=Pad, 1=Ascent, 2=Ejection(Burn), 3=Descent
float maxAltitude = 0.0;
const float dropMargin = 0.5; 
float groundPressure = 0.0;

// Ejection Timer
unsigned long ejectionStartTime = 0;
const unsigned long MOSFET_BURN_TIME = 4000; // 4 seconds to burn the nylon

// Function to handle critical errors
void systemError(String message) {
  Serial.println(message);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, HIGH); // Blue LED indicates Error
  while (1) delay(10); // Halt system
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("\n=== FLIGHT COMPUTER: INIT ===");

  // 1. Configure Output & Input Pins
  pinMode(MOSFET_PIN, OUTPUT);
  digitalWrite(MOSFET_PIN, LOW); 
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);

  // Start with RED LED on (Calibrating/Booting)
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);

  // 2. Initialize Sensors
  if (!bmp.begin(0x76) && !bmp.begin(0x77)) {
    systemError("ERROR: BMP280 not detected!");
  }
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL, Adafruit_BMP280::SAMPLING_X2, Adafruit_BMP280::SAMPLING_X16, Adafruit_BMP280::FILTER_X16, Adafruit_BMP280::STANDBY_MS_500);

  if (!mpu.begin()) {
    systemError("ERROR: MPU6050 not detected!");
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_16_G); 
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // 3. Initialize SD Card
  if (!SD.begin(CS_PIN)) {
    systemError("ERROR: SD Card not detected!");
  }

  // 4. Altitude Calibration
  Serial.println("Calibrating initial altitude...");
  float pressureSum = 0;
  for(int i = 0; i < 20; i++){
    pressureSum += bmp.readPressure();
    delay(100);
  }
  groundPressure = (pressureSum / 20.0) / 100.0F; 

  // 5. Prepare Flight Log File
  File logFile = SD.open("/flight_realtest3_log.csv", FILE_WRITE);
  if (logFile) {
    logFile.println("Time(ms),State,Altitude(m),Accel_X,Accel_Y,Accel_Z,Gyro_X,Gyro_Y,Gyro_Z");
    logFile.close();
  } else {
    systemError("ERROR: Could not create flight_realtest3_log.csv!");
  }

  // System Ready: Turn off RED, turn on GREEN
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, HIGH);
  
  // Audible Warning
  digitalWrite(BUZZER_PIN, HIGH);
  delay(1000);
  digitalWrite(BUZZER_PIN, LOW);
  
  Serial.println("SYSTEM ARMED! Waiting for liftoff...");
}

void loop() {
  unsigned long currentTime = millis();

  // Reset by the miniature button (D32)
  if (digitalRead(BUTTON_PIN) == LOW) {
    digitalWrite(GREEN_LED_PIN, LOW); 
    digitalWrite(BLUE_LED_PIN, HIGH); 
    Serial.println("GROUND COMMAND RECEIVED: Recalibrating Altimeter...");
    delay(1000); 
    ESP.restart(); 
  }

  // A. Read Sensors
  float relativeAltitude = bmp.readAltitude(groundPressure);
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // B. Update Max Altitude
  if (flightState == 1 && relativeAltitude > maxAltitude) {
    maxAltitude = relativeAltitude;
  }

  // C. Finite State Machine
  switch (flightState) {
    case 0: // WAITING ON PAD
      if (relativeAltitude > 1.0) { 
        flightState = 1;
        // Turn off GREEN, turn on BLUE to indicate flight
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(BLUE_LED_PIN, HIGH);
        Serial.println(">>> LIFTOFF DETECTED <<<");
      }
      break;

    case 1: // ASCENT
      if (relativeAltitude < (maxAltitude - dropMargin)) {
        flightState = 2; 
        ejectionStartTime = currentTime;
        
        digitalWrite(MOSFET_PIN, HIGH); // TRIGGER EJECTION BURN
        digitalWrite(BUZZER_PIN, HIGH); 
        digitalWrite(RED_LED_PIN, HIGH); // Add RED led during burn
        
        Serial.println(">>> APOGEE! MOSFET ON <<<");
      }
      break;

    case 2: // EJECTION (MOSFET ON)
      if (currentTime - ejectionStartTime >= MOSFET_BURN_TIME) {
        digitalWrite(MOSFET_PIN, LOW); // CUT POWER
        digitalWrite(BUZZER_PIN, LOW);
        digitalWrite(RED_LED_PIN, LOW); 
        flightState = 3;
        Serial.println(">>> EJECTION COMPLETE. MOSFET OFF <<<");
      }
      break;

    case 3: // DESCENT / LANDING
      break;
  }

  // D. Log Telemetry
  String dataLine = String(currentTime) + "," + 
                    String(flightState) + "," + 
                    String(relativeAltitude) + "," + 
                    String(a.acceleration.x) + "," + 
                    String(a.acceleration.y) + "," + 
                    String(a.acceleration.z) + "," + 
                    String(g.gyro.x) + "," + 
                    String(g.gyro.y) + "," + 
                    String(g.gyro.z);

  File logFile = SD.open("/flight_realtest3_log.csv", FILE_APPEND);
  if (logFile) {
    logFile.println(dataLine);
    logFile.close(); 
  }
  
  Serial.println(dataLine);
  delay(50); 
}