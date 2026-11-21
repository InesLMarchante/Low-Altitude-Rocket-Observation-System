const int mosfetPin = 4;

void setup() {
  Serial.begin(115200);
  pinMode(mosfetPin, OUTPUT);
  digitalWrite(mosfetPin, LOW); // Ensures the gate starts closed!
  
  Serial.println("System Armed. Ejection in 3 seconds...");
  delay(3000); 
}

void loop() {
  Serial.println("IGNITION! (Parachute deployed)");
  digitalWrite(mosfetPin, HIGH); // Opens the MOSFET gate
  
  delay(2000); // Keeps current flowing for 2 seconds (nichrome burn time)
  
  Serial.println("Power cutoff.");
  digitalWrite(mosfetPin, LOW);  // Closes the MOSFET gate
  
  while(1); // System locked. Parachute only deploys once per flight!
}