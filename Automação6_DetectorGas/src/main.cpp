
#include <Arduino.h>

// Pino do sensor MQ-2
const int sensorGas = A0;

// Pinos dos indicadores
const int ledVermelho = 8;
const int buzzer = 9;

// Limite para deteccao de gas
const int limiteGas = 400;

// Controla o estado do alarme
bool alarmeAtivo = false;

void setup() {
  pinMode(sensorGas, INPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(ledVermelho, LOW);
  noTone(buzzer);

  Serial.begin(9600);

  Serial.println("Sistema detector de gas iniciado!");
}

void loop() {
  // Leitura do sensor de gas
  int leituraGas = analogRead(sensorGas);

  // Verifica se a leitura ultrapassou o limite
  bool gasDetectado = leituraGas >= limiteGas;

  // Ativa o alarme quando ha deteccao de gas
  if (gasDetectado && !alarmeAtivo) {
    digitalWrite(ledVermelho, HIGH);
    tone(buzzer, 1000);

    alarmeAtivo = true;

    Serial.println("ALERTA: concentracao de gas elevada!");
  }

  // Desativa o alarme quando a concentracao volta ao normal
  else if (!gasDetectado && alarmeAtivo) {
    digitalWrite(ledVermelho, LOW);
    noTone(buzzer);

    alarmeAtivo = false;

    Serial.println("Concentracao de gas normalizada.");
  }

  delay(500);
}
