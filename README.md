<div align="center">

<img src="https://sesiraidens.github.io/portifolio/assets/logo_color-aNRVU26Y.png" alt="Logo RAIDENS" width="140">

# raidens-arduino

**Biblioteca C++ para Arduino com sensores, motores e exemplos de navegação autônoma**

![Arduino](https://img.shields.io/badge/Arduino-IDE-00979D?style=flat-square&logo=arduino&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-Arduino-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![Sem dependências](https://img.shields.io/badge/depend%C3%AAncias-nenhuma-2EA043?style=flat-square)
![Licença MIT](https://img.shields.io/badge/Licen%C3%A7a-MIT-D9333B?style=flat-square)

[Sobre](#sobre) · [Instalação](#instalação) · [Uso](#uso) · [Exemplos](#exemplos) · [Pinagem](#pinagem-padrão)

</div>

---

## Sobre

O **raidens-arduino** leva para o microcontrolador as mesmas abstrações que a equipe usa em Python: `SensorIR`, `MatrizIR`, `Ultrassonico`, `DriverL298N`, `ServoMotor` e companhia. Quem aprendeu a lógica no [`raidens-python`](https://github.com/sesiraidens/raidens-python) encontra aqui os mesmos nomes e o mesmo raciocínio, agora rodando direto no Arduino.

Além da biblioteca, o repositório guarda sketches independentes para testar um componente isolado e utilitários que aparecem em quase todo projeto.

## Hardware de referência

| Componente | Qtd. |
|---|---|
| Arduino Uno ou Nano | 1 |
| Sensor IR de linha | 5 |
| Ultrassônico HC-SR04 | 1 |
| Driver L298N | 1 |
| Motor DC | 2 |
| Bateria 7,4 V | 1 |

## Instalação

1. Clone o repositório:
   ```bash
   git clone https://github.com/sesiraidens/raidens-arduino.git
   ```
2. Copie `src/sensores.h`, `src/sensores.cpp`, `src/motores.h` e `src/motores.cpp` para a pasta do seu sketch.
3. Abra o `.ino` na Arduino IDE (1.8 ou superior). Nenhuma biblioteca externa é necessária.

## Uso

### Sensores

```cpp
#include "sensores.h"

SensorIR ir(A0);
bool branco = ir.ler();          // false = preto, true = branco

Ultrassonico ultra(9, 10);       // trigger, echo
float distancia = ultra.medirCm();
```

| Classe | Hardware |
|---|---|
| `SensorIR` | Sensor infravermelho individual |
| `MatrizIR` | Barra com 5 sensores IR |
| `Ultrassonico` | HC-SR04 |
| `Encoder` | Encoder de roda |

### Motores

```cpp
#include "motores.h"

DriverL298N motores(5, 2, 3, 6, 4, 7);   // ENA, IN1, IN2, ENB, IN3, IN4
motores.frente(200);
motores.esquerda(150);
motores.parar();

ServoMotor servo(11);
servo.mover(45);
servo.centro();
```

| Classe | Hardware |
|---|---|
| `MotorDC` | Motor DC com PWM |
| `DriverL298N` | Ponte H para dois motores |
| `ServoMotor` | Servo SG90 |
| `MotorPasso` | 28BYJ-48 |

## Exemplos

Abra pela Arduino IDE em **Arquivo → Abrir**.

| Sketch | O que faz |
|---|---|
| `examples/seguidor_linha` | Segue linha preta com 5 sensores IR e PID |
| `examples/controle_distancia` | Mantém 30 cm da parede com o ultrassônico e PID |
| `examples/leitura_sensores` | Lê e imprime todos os sensores no Monitor Serial |
| `sensors/ultrassonico` | Teste isolado do HC-SR04, sem a biblioteca |
| `utilitarios/non_blocking_delay` | Temporização com `millis()` sem travar o `loop()` |

## Pinagem padrão

| Função | Pino |
|---|---|
| IR esquerda → direita | A0, A1, A2, A3, A4 |
| Ultrassônico trigger / echo | 9 / 10 |
| Motor esquerdo (ENA) | 5 |
| Motor direito (ENB) | 6 |
| Servo | 11 |

## Estrutura

```text
raidens-arduino/
├── src/           # Biblioteca: sensores e motores (.h/.cpp)
├── examples/      # Projetos completos que usam a biblioteca
├── sensors/       # Testes isolados de um componente
└── utilitarios/   # Padrões reutilizáveis, como delay não bloqueante
```

## Ecossistema RAIDENS

Este repositório faz parte de um conjunto de bibliotecas da equipe. Elas usam os mesmos nomes de classes e convenções, então o que você aprende em uma serve nas outras.

| Repositório | Para quê |
|---|---|
| [`raidens-python`](https://github.com/sesiraidens/raidens-python) | Biblioteca principal em Python: sensores, motores e robôs prontos (seguidor, parede, resgate) |
| [`raidens-sensores`](https://github.com/sesiraidens/raidens-sensores) | Catálogo completo de sensores com calibração e filtragem |
| [`raidens-motores`](https://github.com/sesiraidens/raidens-motores) | Motores DC, servo, passo, driver L298N e rodas mecanum |
| [`raidens-pid`](https://github.com/sesiraidens/raidens-pid) | Controladores PID, PID avançado, cascata e sintonia Ziegler-Nichols |
| [`raidens-opencv`](https://github.com/sesiraidens/raidens-opencv) | Visão computacional: cores, linhas e navegação por câmera |
| [`raidens-lab`](https://github.com/sesiraidens/raidens-lab) | Calibração interativa de cores em HSV e LAB |
| [`raidens-obr`](https://github.com/sesiraidens/raidens-obr) | Robô completo para a OBR, integrando sensores, motores e missões |
| [`raidens-electronics`](https://github.com/sesiraidens/raidens-electronics) | Cálculos e modelos de componentes eletrônicos |
| [`raidens-3d`](https://github.com/sesiraidens/raidens-3d) | Peças 3D paramétricas geradas em OpenSCAD |
| [`raidens-ros`](https://github.com/sesiraidens/raidens-ros) | Estrutura de nodes e tópicos ROS 2 |
| [`raidens-snippets`](https://github.com/sesiraidens/raidens-snippets) | Trechos de código prontos para copiar e colar |

---

<div align="center">

<img src="https://sesiraidens.github.io/portifolio/assets/logo_color-aNRVU26Y.png" alt="Logo RAIDENS" width="56">

**Equipe RAIDENS** · SESI 192 Alumínio/SP

[![Email](https://img.shields.io/badge/Email-sesiraidens%40gmail.com-D14836?style=flat-square&logo=gmail&logoColor=white)](mailto:sesiraidens@gmail.com)
[![Linktree](https://img.shields.io/badge/Linktree-sesiraidens-39E06B?style=flat-square&logo=linktree&logoColor=white)](https://linktr.ee/sesiraidens)
[![GitHub](https://img.shields.io/badge/GitHub-sesiraidens-181717?style=flat-square&logo=github&logoColor=white)](https://github.com/sesiraidens)

<sub>Desenvolvido pela equipe RAIDENS para fins educacionais. Licenciado sob MIT.</sub>

</div>
