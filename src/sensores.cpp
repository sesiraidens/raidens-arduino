#include "sensoreh"

// === SensorIR ===

SensorIR::SensorIR(uint8_t pin, int limiar) {
    this->pin = pin;
    this->limiar = limiar;
    pinMode(pin, INPUT);
}

int SensorIR::lerBruto() {
    return analogRead(pin);
}

bool SensorIR::ler() {
    return analogRead(pin) > limiar;
}

float SensorIR::lerProporcao() {
    return analogRead(pin) / 1023.0;
}

void SensorIR::calibrar() {
    limiar = analogRead(pin);
}

void SensorIR::configurarLimiar(int limiar) {
    this->limiar = limiar;
}

// === MatrizIR ===

MatrizIR::MatrizIR(uint8_t pins[5]) {
    int pesosPadrao[] = {-2, -1, 0, 1, 2};
    for (int i = 0; i < 5; i++) {
        sensores[i] = new SensorIR(pins[i]);
        pesos[i] = pesosPadrao[i];
    }
}

void MatrizIR::lerTudo(bool leituras[5]) {
    for (int i = 0; i < 5; i++) {
        leituras[i] = sensores[i]->ler();
    }
}

float MatrizIR::calcularPosicao() {
    float somaPesos = 0;
    int somaLeituras = 0;
    
    for (int i = 0; i < 5; i++) {
        bool leitura = sensores[i]->ler();
        if (!leitura) {
            somaPesos += pesos[i];
            somaLeituras++;
        }
    }
    
    if (somaLeituras == 0) return 0;
    return somaPesos / somaLeituras;
}

bool MatrizIR::linhaDetectada() {
    for (int i = 0; i < 5; i++) {
        if (!sensores[i]->ler()) return true;
    }
    return false;
}

void MatrizIR::calibrarTodos() {
    for (int i = 0; i < 5; i++) {
        sensores[i]->calibrar();
    }
}

// === Ultrassonico ===

Ultrassonico::Ultrassonico(uint8_t trigger, uint8_t echo) {
    this->pinTrigger = trigger;
    this->pinEcho = echo;
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
}

float Ultrassonico::medirCm() {
    digitalWrite(pinTrigger, LOW);
    delayMicroseconds(2);
    digitalWrite(pinTrigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrigger, LOW);
    
    long duracao = pulseIn(pinEcho, HIGH, 30000);
    return duracao * 0.034 / 2.0;
}

float Ultrassonico::medirM() {
    return medirCm() / 100.0;
}

// === Encoder ===

Encoder::Encoder(uint8_t pinA, uint8_t pinB, int ppr) {
    this->pinA = pinA;
    this->pinB = pinB;
    this->ppr = ppr;
    this->contador = 0;
    this->circunferenciaRoda = 21.99;
    
    pinMode(pinA, INPUT);
    pinMode(pinB, INPUT);
}

void Encoder::incrementar() {
    contador++;
}

void Encoder::decrementar() {
    contador--;
}

float Encoder::velocidade(float tempoSegundos) {
    float revolucoes = contador / (float)ppr;
    float distancia = revolucoes * circunferenciaRoda;
    contador = 0;
    return distancia / tempoSegundos;
}

float Encoder::distancia() {
    float revolucoes = contador / (float)ppr;
    return revolucoes * circunferenciaRoda;
}

void Encoder::reset() {
    contador = 0;
}
