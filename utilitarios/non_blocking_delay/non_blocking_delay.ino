// Raidens - Delay Nao-Bloqueante
// Usa millis() para nao bloquear o loop

unsigned long ultimoTempo = 0;
const unsigned long intervalo = 1000; // 1 segundo

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  unsigned long tempoAtual = millis();
  
  if (tempoAtual - ultimoTempo >= intervalo) {
    ultimoTempo = tempoAtual;
    digitalWrite(13, !digitalRead(13));
    Serial.println("Toggle LED");
  }
  
  // Outro codigo pode rodar aqui sem bloquear
}