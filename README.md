<div align="center">

<img src="https://sesiraidens.github.io/portifolio/assets/logo_color-aNRVU26Y.png" width="80">

# raidens-arduino

Biblioteca C++ para Arduino com sensores, motores e navegacao autonoma.

![Arduino](https://img.shields.io/badge/Arduino-00979D?style=flat&logo=arduino&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=flat&logo=cplusplus&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-d9333b?style=flat)
![Status](https://img.shields.io/badge/Status-Active-2ea043?style=flat)

</div>

---

## Sobre

O **raidens-arduino** fornece classes C++ para Arduino, facilitando o uso de sensores e motores em robos. Inclui suporte a sensores IR, ultrassonico, encoders, motores DC, servos e motores de passo.

---

## Estrutura

`
raidens-arduino/
├── src/
│   ├── sensores.h       # Header de sensores
│   ├── sensores.cpp     # Implementacao de sensores
│   ├── motores.h        # Header de motores
│   └── motores.cpp      # Implementacao de motores
├── examples/
│   ├── seguidor_linha/
│   │   └── seguidor_linha.ino
│   ├── controle_distancia/
│   │   └── controle_distancia.ino
│   └── leitura_sensores/
│       └── leitura_sensores.ino
└── README.md
`

---

## Modulos

### Sensores

| Classe | Descricao |
|---|---|
| SensorIR | Sensor infravermelho individual |
| MatrizIR | Matriz de 5 sensores para linha |
| Ultrassonico | HC-SR04 para distancia |
| Encoder | Encoder de motor |

**Uso basico:**
`cpp
#include "sensoreh"

SensorIR ir(A0);
bool leitura = ir.ler();  // false=preto, true=branco

Ultrassonico ultra(9, 10);
float distancia = ultra.medirCm();
`

### Motores

| Classe | Descricao |
|---|---|
| MotorDC | Motor DC com PWM |
| DriverL298N | Driver para 2 motores |
| ServoMotor | Servo SG90 angular |
| MotorPasso | Motor de passo 28BYJ-48 |

**Uso basico:**
`cpp
#include "motoresh"

DriverL298N motores(5, 2, 3, 6, 4, 7);
motores.frente(200);
motores.esquerda(150);
motores.parar();

ServoMotor servo(11);
servo.mover(45);
servo.centro();
`

---

## Exemplos

### Seguidor de Linha

`ash
# Abrir no Arduino IDE
File -> Open -> examples/seguidor_linha/seguidor_linha.ino
`

Usa 5 sensores IR com PID para seguir linha preta.

### Controle de Distancia

`ash
File -> Open -> examples/controle_distancia/controle_distancia.ino
`

Usa ultrassonico com PID para manter 30cm de parede.

### Leitura de Sensores

`ash
File -> Open -> examples/leitura_sensores/leitura_sensores.ino
`

Le e imprime valores de todos os sensores.

---

## Hardware Necessario

| Componente | Quantidade |
|---|---|
| Arduino Uno/Nano | 1 |
| Sensor IR | 5 |
| Ultrassonico HC-SR04 | 1 |
| Driver L298N | 1 |
| Motor DC | 2 |
| Bateria 7.4V | 1 |

---

## Configuracao

### Pinos Padrao

| Funcao | Pino |
|---|---|
| IR Esquerda | A0 |
| IR Centro-Esquerda | A1 |
| IR Centro | A2 |
| IR Centro-Direita | A3 |
| IR Direita | A4 |
| Ultrassonico Trigger | 9 |
| Ultrassonico Echo | 10 |
| Motor Esquerdo ENA | 5 |
| Motor Direito ENB | 6 |
| Servo | 11 |

---

## Dependencias

- Arduino IDE 1.8+
- Nenhuma biblioteca externa necessaria

---

## Equipe

**RAIDENS - SESI Aluminio 192**

Desenvolvido para uso interno da equipe. Licenciado sob MIT.