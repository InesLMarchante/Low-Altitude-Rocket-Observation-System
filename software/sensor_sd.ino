#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_MPU6050.h>

Adafruit_BMP280 bmp;
Adafruit_MPU6050 mpu;
const int CS_PIN = 5;

float pressaoAoNivelDoChao = 0;

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("\n=== INICIAÇÃO DO COMPUTADOR DE VOO ===");

  if (!bmp.begin(0x76)) {
    Serial.println("ERRO: BMP280 não detetado!");
    while (1) delay(10);
  }
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL, Adafruit_BMP280::SAMPLING_X2, Adafruit_BMP280::SAMPLING_X16, Adafruit_BMP280::FILTER_X16, Adafruit_BMP280::STANDBY_MS_500);

  if (!mpu.begin()) {
    Serial.println("ERRO: MPU6050 não detetado!");
    while (1) delay(10);
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  if (!SD.begin(CS_PIN)) {
    Serial.println("ERRO: Cartão SD não detetado!");
    while (1) delay(10);
  }

  // Lê a pressão local para usar como referência do chão
  pressaoAoNivelDoChao = bmp.readPressure() / 100.0F; // Convertido para hPa
  Serial.print("Calibração concluída. Pressão local: ");
  Serial.print(pressaoAoNivelDoChao);
  Serial.println(" hPa");

  // 5. Preparar Ficheiro de Log
  File log = SD.open("/dados_voo3.csv", FILE_WRITE);
  if (log) {

    log.println("Tempo(ms),Altitude(m),Acel_X,Acel_Y,Acel_Z,Giro_X,Giro_Y,Giro_Z");
    log.close();
    Serial.println("Sistema Pronto! A iniciar gravação de telemetria...\n");
  } else {
    Serial.println("ERRO ao criar dados_voo.csv!");
  }
}

void loop() {
  // Capturar dados inerciais
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Capturar altitude relativa 
  float altitudeRelativa = bmp.readAltitude(pressaoAoNivelDoChao);
  unsigned long tempoAtual = millis();

  String linhaDados = String(tempoAtual) + "," + 
                      String(altitudeRelativa) + "," + 
                      String(a.acceleration.x) + "," + 
                      String(a.acceleration.y) + "," + 
                      String(a.acceleration.z) + "," + 
                      String(g.gyro.x) + "," + 
                      String(g.gyro.y) + "," + 
                      String(g.gyro.z);

  // Imprimir na Consola (para monitorização ao vivo)
  Serial.println(linhaDados);

  // Gravar no Cartão SD
  File log = SD.open("/dados_voo3.csv", FILE_APPEND);
  if (log) {
    log.println(linhaDados);
    log.close(); 
  }

  // Grava a 10Hz (10 vezes por segundo)
  delay(100); 
}