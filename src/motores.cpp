#include "motoresh"

// === MotorDC ===

MotorDC::MotorDC(uint8_t pinVelocidade, uint8_t pinDirecao) {
    this->pinVelocidade = pinVelocidade;
    this->pinDirecao = pinDirecao;
    this->velocidadeAtual = 0;
    
    pinMode(pinVelocidade, OUTPUT);
    pinMode(pinDirecao, OUTPUT);
}

void MotorDC::forward(int velocidade) {
    velocidadeAtual = constrain(velocidade, 0, 255);
    digitalWrite(pinDirecao, HIGH);
    analogWrite(pinVelocidade, velocidadeAtual);
}

void MotorDC::backward(int velocidade) {
    velocidadeAtual = constrain(velocidade, 0, 255);
    digitalWrite(pinDirecao, LOW);
    analogWrite(pinVelocidade, velocidadeAtual);
}

void MotorDC::stop() {
    velocidadeAtual = 0;
    analogWrite(pinVelocidade, 0);
}

void MotorDC::brake() {
    velocidadeAtual = 0;
    analogWrite(pinVelocidade, 0);
    digitalWrite(pinDirecao, HIGH);
}

void MotorDC::setVelocidade(int velocidade) {
    if (velocidade >= 0) {
        forward(velocidade);
    } else {
        backward(-velocidade);
    }
}

// === DriverL298N ===

DriverL298N::DriverL298N(uint8_t pinEna, uint8_t pinIn1, uint8_t pinIn2,
                           uint8_t pinEnb, uint8_t pinIn3, uint8_t pinIn4)
    : motorEsquerdo(pinEna, pinIn1), motorDireito(pinEnb, pinIn3) {
}

void DriverL298N::mover(int esquerdo, int direito) {
    motorEsquerdo.setVelocidade(esquerdo);
    motorDireito.setVelocidade(direito);
}

void DriverL298N::frente(int velocidade) {
    mover(velocidade, velocidade);
}

void DriverL298N::tras(int velocidade) {
    mover(-velocidade, -velocidade);
}

void DriverL298N::esquerda(int velocidade) {
    mover(-velocidade, velocidade);
}

void DriverL298N::direita(int velocidade) {
    mover(velocidade, -velocidade);
}

void DriverL298N::parar() {
    mover(0, 0);
}

// === ServoMotor ===

ServoMotor::ServoMotor(uint8_t pin) {
    this->pin = pin;
    this->anguloAtual = 90;
    this->anguloMin = 0;
    this->anguloMax = 180;
    
    pinMode(pin, OUTPUT);
}

void ServoMotor::mover(int angulo) {
    anguloAtual = constrain(angulo, anguloMin, anguloMax);
    int pulso = map(anguloAtual, 0, 180, 544, 2400);
    digitalWrite(pin, HIGH);
    delayMicroseconds(pulso);
    digitalWrite(pin, LOW);
}

void ServoMotor::centro() {
    mover(90);
}

void ServoMotor::esquerda() {
    mover(anguloMin);
}

void ServoMotor::direita() {
    mover(anguloMax);
}

void ServoMotor::incrementar(int angulo) {
    mover(anguloAtual + angulo);
}

void ServoMotor::decrementar(int angulo) {
    mover(anguloAtual - angulo);
}

// === MotorPasso ===

const int MotorPasso::sequencia[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
};

MotorPasso::MotorPasso(uint8_t pins[4]) {
    this->posicaoAtual = 0;
    for (int i = 0; i < 4; i++) {
        this->pins[i] = pins[i];
        pinMode(pins[i], OUTPUT);
    }
}

void MotorPasso::passo(int direcao, int delayMs) {
    for (int s = 0; s < 4; s++) {
        for (int p = 0; p < 4; p++) {
            int idx = (direcao == 1) ? p : (3 - p);
            digitalWrite(pins[p], sequencia[s][idx]);
        }
        delay(delayMs);
    }
    posicaoAtual += direcao;
}

void MotorPasso::moverPassos(int numPassos, int direcao) {
    for (int i = 0; i < abs(numPassos); i++) {
        passo(direcao);
    }
}

void MotorPasso::revolucao(int direcao) {
    moverPassos(passosPorRevolucao, direcao);
}

void MotorPasso::graus(int angulo, int direcao) {
    int passos = (long)passosPorRevolucao * angulo / 360;
    moverPassos(passos, direcao);
}

int MotorPasso::posicao() {
    return posicaoAtual;
}

void MotorPasso::reset() {
    posicaoAtual = 0;
}



