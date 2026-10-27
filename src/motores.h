/*
 * motores.h
 * 
 * Biblioteca para controle de motores em Arduino.
 */

#ifndef MOTORES_H
#define MOTORES_H

#include <Arduino.h>

// Motor DC
class MotorDC {
private:
    uint8_t pinVelocidade;
    uint8_t pinDirecao;
    int velocidadeAtual;
    
public:
    MotorDC(uint8_t pinVelocidade, uint8_t pinDirecao);
    void forward(int velocidade = 255);
    void backward(int velocidade = 255);
    void stop();
    void brake();
    void setVelocidade(int velocidade);
};

// Driver L298N
class DriverL298N {
private:
    MotorDC motorEsquerdo;
    MotorDC motorDireito;
    
public:
    DriverL298N(uint8_t pinEna, uint8_t pinIn1, uint8_t pinIn2,
                uint8_t pinEnb, uint8_t pinIn3, uint8_t pinIn4);
    void mover(int esquerdo, int direito);
    void frente(int velocidade = 255);
    void tras(int velocidade = 255);
    void esquerda(int velocidade = 255);
    void direita(int velocidade = 255);
    void parar();
};

// Servo Motor
class ServoMotor {
private:
    uint8_t pin;
    int anguloAtual;
    int anguloMin;
    int anguloMax;
    
public:
    ServoMotor(uint8_t pin);
    void mover(int angulo);
    void centro();
    void esquerda();
    void direita();
    void incrementar(int angulo = 5);
    void decrementar(int angulo = 5);
};

// Motor de Passo 28BYJ-48
class MotorPasso {
private:
    uint8_t pins[4];
    int posicaoAtual;
    static const int passosPorRevolucao = 2048;
    static const int sequencia[4][4];
    
public:
    MotorPasso(uint8_t pins[4]);
    void passo(int direcao = 1, int delayMs = 2);
    void moverPassos(int numPassos, int direcao = 1);
    void revolucao(int direcao = 1);
    void graus(int angulo, int direcao = 1);
    int posicao();
    void reset();
};

#endif

