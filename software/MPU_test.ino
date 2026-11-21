#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);
  
  // Pequeno atraso para a consola abrir
  delay(2000);
  Serial.println("A iniciar o MPU6050...");

  if (!mpu.begin()) {
    Serial.println("Erro: Não foi possível encontrar o MPU6050. Verifica os fios!");
    while (1) delay(10);
  }
  
  Serial.println("MPU6050 encontrado com sucesso!");
  
  // Configurações base para o voo
  mpu.setAccelerometerRange(MPU6050_RANGE_16_G); // Para aguentar a aceleração do motor do foguete
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.println("--- Dados Inerciais ---");
  
  // Aceleração em m/s^2 (Forças G)
  Serial.print("Aceleração X: "); Serial.print(a.acceleration.x); Serial.print(" | ");
  Serial.print("Y: "); Serial.print(a.acceleration.y); Serial.print(" | ");
  Serial.print("Z: "); Serial.print(a.acceleration.z); Serial.println(" m/s^2");

  // Rotação em radianos por segundo
  Serial.print("Rotação    X: "); Serial.print(g.gyro.x); Serial.print(" | ");
  Serial.print("Y: "); Serial.print(g.gyro.y); Serial.print(" | ");
  Serial.print("Z: "); Serial.print(g.gyro.z); Serial.println(" rad/s");
  
  Serial.println();
  delay(1000);
}