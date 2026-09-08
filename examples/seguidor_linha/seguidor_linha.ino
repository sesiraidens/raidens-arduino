/*
 * seguidor_linha.ino
 * 
 * Seguidor de linha com PID para Arduino.
 * Usa 5 sensores IR e driver L298N.
 */

#include "sensoreh"
#include "motoresh"

// Pinos dos sensores IR
uint8_t pinsIR[] = {A0, A1, A2, A3, A4};

// Pinos do driver L298N
#define PIN_ENA 5
#define PIN_IN1 2
#define PIN_IN2 3
#define PIN_ENB 6
#define PIN_IN3 4
#define PIN_IN4 7

// Variaveis PID
float Kp = 2.5;
float Ki = 0.8;
float Kd = 0.3;

float erroAnterior = 0;
float integral = 0;
int velocidadeBase = 150;

// Objetos
MatrizIR sensores(pinsIR);
DriverL298N motores(PIN_ENA, PIN_IN1, PIN_IN2, PIN_ENB, PIN_IN3, PIN_IN4);

void setup() {
    Serial.begin(9600);
    
    Serial.println("Calibrando sensores...");
    sensores.calibrarTodos();
    delay(1000);
    
    Serial.println("Seguidor de linha iniciado.");
}

void loop() {
    if (!sensores.linhaDetectada()) {
        motores.parar();
        Serial.println("Linha perdida!");
        delay(1000);
        return;
    }
    
    float posicao = sensores.calcularPosicao();
    
    float erro = posicao;
    integral += erro;
    float derivada = erro - erroAnterior;
    
    float correcao = Kp * erro + Ki * integral + Kd * derivada;
    
    erroAnterior = erro;
    
    int velEsq = velocidadeBase + correcao;
    int velDir = velocidadeBase - correcao;
    
    velEsq = constrain(velEsq, -255, 255);
    velDir = constrain(velDir, -255, 255);
    
    motores.mover(velEsq, velDir);
    
    Serial.print("Pos: ");
    Serial.print(posicao);
    Serial.print(" | Corr: ");
    Serial.println(correcao);
    
    delay(10);
}
