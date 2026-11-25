
#include <Arduino.h>

// Definicao dos pinos
const int sensorPorta = 2;
const int buzzer = 8;

// Armazena o estado anterior da porta
int estadoAnterior = LOW;

void setup() {
  pinMode(sensorPorta, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

  Serial.println("Sistema de alarme iniciado!");
}

void loop() {
  // Leitura do sensor magnetico
  int estadoPorta = digitalRead(sensorPorta);

  // Verifica se houve mudanca no estado da porta
  if (estadoPorta != estadoAnterior) {

    if (estadoPorta == HIGH) {
      tone(buzzer, 1000);

      Serial.println("Porta aberta! Alarme ativado.");
    } 
    else {
      noTone(buzzer);

      Serial.println("Porta fechada! Alarme desativado.");
    }

    // Atualiza o estado anterior
    estadoAnterior = estadoPorta;
  }

  delay(50);
}
