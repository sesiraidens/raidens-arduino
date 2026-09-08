// Raidens - Sensor Ultrassonico HC-SR04
// Mede distancia em centimetros

const int TRIG_PIN = 9;
const int ECHO_PIN = 10;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

float medirDistancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duracao = pulseIn(ECHO_PIN, HIGH);
  float distancia = duracao * 0.034 / 2.0;
  return distancia;
}

void loop() {
  float dist = medirDistancia();
  Serial.print("Distancia: ");
  Serial.print(dist);
  Serial.println(" cm");
  delay(100);
}