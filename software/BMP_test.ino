#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

// Instanciação do objeto do sensor para comunicação I2C
Adafruit_BMP280 bmp; 

void setup() {
  // Inicia a comunicação com a consola do computador a 115200 baud
  Serial.begin(115200);
  
  // Pequeno atraso para garantir que a consola abre a tempo de ler a primeira mensagem
  delay(2000); 
  Serial.println(F("A iniciar o teste do Barómetro BMP280 (Telemetria do Foguete)..."));

  // Inicializa o sensor. O endereço 0x76 é o mais comum para estes módulos roxos HW-611.
  // Se por acaso der erro, podes experimentar trocar para 0x77.
  if (!bmp.begin(0x76)) {
    Serial.println(F("Erro CRÍTICO: Não foi possível encontrar o BMP280."));
    Serial.println(F("Verifica as ligações: VCC->3V3, GND->GND, SDA->D21, SCL->D22"));
    while (1) delay(10); // Fica preso num ciclo infinito se houver falha de hardware
  }

  Serial.println(F("BMP280 inicializado com sucesso!"));

  // Configuração recomendada da Adafruit para leitura de dados estáveis no ar
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Modo de operação contínuo */
                  Adafruit_BMP280::SAMPLING_X2,     /* Oversampling de temperatura */
                  Adafruit_BMP280::SAMPLING_X16,    /* Oversampling de pressão (melhora precisão da altitude) */
                  Adafruit_BMP280::FILTER_X16,      /* Filtragem de pequenas perturbações/ruído */      
                  Adafruit_BMP280::STANDBY_MS_500); /* Tempo de espera entre leituras internas */
}

void loop() {
  Serial.println(F("--- Dados do Sensor ---"));
  
  // 1. Ler e imprimir a Temperatura
  Serial.print(F("Temperatura: "));
  Serial.print(bmp.readTemperature());
  Serial.println(F(" *C"));

  // 2. Ler e imprimir a Pressão Absoluta
  Serial.print(F("Pressão: "));
  Serial.print(bmp.readPressure());
  Serial.println(F(" Pa"));

  // 3. Ler e imprimir a Altitude
  // O valor 1013.25 é a pressão atmosférica média ao nível do mar. 
  Serial.print(F("Altitude Aprox: "));
  Serial.print(bmp.readAltitude(1013.25)); 
  Serial.println(F(" m"));

  Serial.println(); // Linha em branco para facilitar a leitura
  
  // Atraso de 1 segundo (1000 milissegundos) para não inundar o ecrã com texto
  delay(1000); 
}