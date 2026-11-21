#include <SPI.h>
#include <SD.h>

// Definir o pino Chip Select que escolhemos
const int CS_PIN = 5;

void setup() {
  Serial.begin(115200);
  delay(2000); 
  
  Serial.println("\n--- Teste do Sistema de Armazenamento ---");
  Serial.println("A iniciar o módulo de Cartão SD...");
  
  // 1. Tentar comunicar com o cartão
  if (!SD.begin(CS_PIN)) {
    Serial.println("ERRO CRÍTICO: Cartão não detetado!");
    Serial.println("Verifica se: 1) O cartão está bem encaixado, 2) As ligações MISO/MOSI/SCK estão corretas.");
    while (1) delay(10); // Fica preso aqui se falhar
  }
  
  Serial.println("Cartão SD montado com sucesso!");
  
  // 2. Abrir (ou criar) o ficheiro em modo de escrita
  // Nota: A barra "/" antes do nome é obrigatória no ESP32!
  File ficheiro = SD.open("/voo.txt", FILE_WRITE);
  
  // 3. Escrever os dados
  if (ficheiro) {
    Serial.println("A escrever no ficheiro voo.txt...");
    
    ficheiro.println("====================================");
    ficheiro.println("Telemetria do Foguete - INICIALIZADA");
    ficheiro.println("Altitude(m) | Acel.Z(m/s2) | Rotação");
    ficheiro.println("====================================");
    
    // 4. REGRA DE OURO: Fechar sempre o ficheiro!
    ficheiro.close(); 
    
    Serial.println("Gravação concluída com sucesso!");
    Serial.println("Podes retirar o cartão e ir lê-lo no computador.");
  } else {
    Serial.println("ERRO: Não foi possível criar ou abrir o ficheiro voo.txt");
  }
}

void loop() {
  // Para este teste de hardware, não precisamos de repetir nada no loop.
}