// Define o pino onde ligaste o fio vermelho
const int pinoBuzzer = 15;

void setup() {
  // Diz ao ESP32 que este pino vai enviar energia (OUTPUT)
  pinMode(pinoBuzzer, OUTPUT);
}

void loop() {
  // 1. Liga o Buzzer (Apita)
  digitalWrite(pinoBuzzer, HIGH);
  delay(500); // Espera meio segundo
  
  // 2. Desliga o Buzzer (Silêncio)
  digitalWrite(pinoBuzzer, LOW);
  delay(500); // Espera meio segundo
}