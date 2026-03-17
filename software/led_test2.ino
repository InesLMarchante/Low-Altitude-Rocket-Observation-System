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