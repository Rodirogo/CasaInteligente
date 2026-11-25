
#include <Arduino.h>

// Definicao dos pinos
const int sensorPIR = 2;
const int lampada = 13;

// Tempo que a iluminacao permanece ligada
const unsigned long tempoLigada = 5000;

// Armazena o instante da ultima deteccao
unsigned long ultimaDeteccao = 0;

// Controla o estado da iluminacao
bool iluminacaoLigada = false;

void setup() {
  pinMode(sensorPIR, INPUT);
  pinMode(lampada, OUTPUT);

  digitalWrite(lampada, LOW);

  Serial.begin(9600);

  Serial.println("Sistema de iluminacao iniciado!");
}

void loop() {
  // Leitura do sensor de presenca
  int movimento = digitalRead(sensorPIR);

  // Se houver movimento, atualiza o temporizador
  if (movimento == HIGH) {
    ultimaDeteccao = millis();

    if (!iluminacaoLigada) {
      digitalWrite(lampada, HIGH);
      iluminacaoLigada = true;

      Serial.println("Movimento detectado: luz ligada.");
    }
  }

  // Desliga a luz apos 5 segundos sem movimento
  if (iluminacaoLigada &&
      millis() - ultimaDeteccao >= tempoLigada) {

    digitalWrite(lampada, LOW);
    iluminacaoLigada = false;

    Serial.println("Sem movimento: luz desligada.");
  }
}
