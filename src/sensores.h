/*
 * raidens-arduino
 * 
 * Biblioteca para leitura de sensores em Arduino.
 * Inclui sensores IR, ultrassonico, cor e encoders.
 */

#ifndef SENSORES_H
#define SENSORES_H

#include <Arduino.h>

// Sensor IR
class SensorIR {
private:
    uint8_t pin;
    int limiar;
    
public:
    SensorIR(uint8_t pin, int limiar = 512);
    int lerBruto();
    bool ler();
    float lerProporcao();
    void calibrar();
    void configurarLimiar(int limiar);
};

// Matriz IR (5 sensores)
class MatrizIR {
private:
    SensorIR* sensores[5];
    int pesos[5];
    
public:
    MatrizIR(uint8_t pins[5]);
    void lerTudo(bool leituras[5]);
    float calcularPosicao();
    bool linhaDetectada();
    void calibrarTodos();
};

// Ultrassonico
class Ultrassonico {
private:
    uint8_t pinTrigger;
    uint8_t pinEcho;
    
public:
    Ultrassonico(uint8_t trigger, uint8_t echo);
    float medirCm();
    float medirM();
};

// Encoder
class Encoder {
private:
    volatile long contador;
    uint8_t pinA;
    uint8_t pinB;
    float circunferenciaRoda;
    int ppr;
    
public:
    Encoder(uint8_t pinA, uint8_t pinB, int ppr = 20);
    void incrementar();
    void decrementar();
    float velocidade(float tempoSegundos);
    float distancia();
    void reset();
};

#endif
