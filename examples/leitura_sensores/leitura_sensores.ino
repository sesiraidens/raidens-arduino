/*
 * leitura_sensores.ino
 * 
 * Exemplo basico de leitura de todos os sensores.
 */

#include "sensoreh"

// Pinos
uint8_t pinsIR[] = {A0, A1, A2, A3, A4};
#define PIN_TRIGGER 9
#define PIN_ECHO 10

// Objetos
MatrizIR sensores(pinsIR);
Ultrassonico ultrassonico(PIN_TRIGGER, PIN_ECHO);

void setup() {
    Serial.begin(9600);
    Serial.println("Leitura de sensores iniciada.");
    
    sensores.calibrarTodos();
}

void loop() {
    // Leitura IR
    bool leituras[5];
    sensores.lerTudo(leituras);
    
    Serial.print("IR: ");
    for (int i = 0; i < 5; i++) {
        Serial.print(leituras[i] ? "." : "#");
    }
    
    float posicao = sensores.calcularPosicao();
    Serial.print(" | Pos: ");
    Serial.print(posicao);
    
    // Leitura ultrassonico
    float distancia = ultrassonico.medirCm();
    Serial.print(" | Dist: ");
    Serial.print(distancia);
    Serial.println("cm");
    
    delay(200);
}
