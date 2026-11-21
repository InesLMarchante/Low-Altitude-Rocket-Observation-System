#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

const int pinoLedVermelho = 12;
const int pinoLedVerde = 13;
const int pinoLedAzul = 14;
float altitude_base = 0.0;

void setup() {
  Serial.begin(115200);
  
  pinMode(pinoLedVermelho, OUTPUT);
  pinMode(pinoLedVerde, OUTPUT);
  pinMode(pinoLedAzul, OUTPUT);
  
  // 1. Arranca com o Vermelho
  digitalWrite(pinoLedVermelho, HIGH); 
  digitalWrite(pinoLedVerde, LOW); 
  digitalWrite(pinoLedAzul, LOW);

  Serial.println("A procurar BMP280...");
  
  // 2. Verifica APENAS o BMP280
  if (!bmp.begin(0x76) && !bmp.begin(0x77)) {
    Serial.println("ERRO: BMP280 desligado!");
    digitalWrite(pinoLedVermelho, LOW);
    digitalWrite(pinoLedAzul, HIGH); // Acende Azul
    while (1); 
  }

  // 3. Calibração (Demora 1 segundo)
  Serial.println("A calibrar a altitude...");
  float soma_alt = 0;
  for(int i = 0; i < 10; i++){
    soma_alt += bmp.readAltitude(1013.25);
    delay(100);
  }
  altitude_base = soma_alt / 10.0;
  
  // 4. Tudo OK
  digitalWrite(pinoLedVermelho, LOW);
  digitalWrite(pinoLedVerde, HIGH); // Acende Verde
  Serial.println("PRONTO: Luz Verde!");
}

void loop() {
  // Para este teste de LEDs de arranque, o loop pode ficar vazio
}