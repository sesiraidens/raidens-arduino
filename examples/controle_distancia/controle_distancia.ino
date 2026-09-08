/*
 * controle_distancia.ino
 * 
 * Controle de distancia com ultrassonico.
 * Mantem distancia constante de parede.
 */

#include "sensoreh"
#include "motoresh"

// Pinos
#define PIN_TRIGGER 9
#define PIN_ECHO 10
#define PIN_ENA 5
#define PIN_IN1 2
#define PIN_IN2 3
#define PIN_ENB 6
#define PIN_IN3 4
#define PIN_IN4 7

// Variaveis PID
float Kp = 2.0;
float Ki = 0.5;
float Kd = 0.2;

float erroAnterior = 0;
float integral = 0;
float distanciaAlvo = 30.0;

// Objetos
Ultrassonico ultrassonico(PIN_TRIGGER, PIN_ECHO);
DriverL298N motores(PIN_ENA, PIN_IN1, PIN_IN2, PIN_ENB, PIN_IN3, PIN_IN4);

void setup() {
    Serial.begin(9600);
    Serial.println("Controle de distancia iniciado.");
    Serial.print("Distancia alvo: ");
    Serial.print(distanciaAlvo);
    Serial.println(" cm");
}

void loop() {
    float distancia = ultrassonico.medirCm();
    
    float erro = distancia - distanciaAlvo;
    integral += erro;
    integral = constrain(integral, -50, 50);
    float derivada = erro - erroAnterior;
    
    float correcao = Kp * erro + Ki * integral + Kd * derivada;
    
    erroAnterior = erro;
    
    int velocidade = constrain((int)correcao, -255, 255);
    
    motores.mover(velocidade, velocidade);
    
    Serial.print("Dist: ");
    Serial.print(distancia);
    Serial.print("cm | Vel: ");
    Serial.println(velocidade);
    
    delay(100);
}
