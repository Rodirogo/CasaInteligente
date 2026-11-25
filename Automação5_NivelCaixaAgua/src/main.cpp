
#include <Arduino.h>

// Pinos do sensor ultrassonico HC-SR04
const int trigPin = 2;
const int echoPin = 3;

// Pinos dos LEDs
const int ledVerde = 4;
const int ledAmarelo = 5;
const int ledVermelho = 6;

// Pino do buzzer
const int buzzer = 8;

// Altura considerada para a caixa d'agua
const float alturaCaixa = 30.0;

// Armazena a ultima categoria identificada
int ultimoEstado = -1;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

  pinMode(buzzer, OUTPUT);

  Serial.println("Sistema de monitoramento da caixa d'agua iniciado!");
}

void loop() {
  // Envia um pulso ultrassonico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Recebe o tempo de retorno do sinal
  long duracao = pulseIn(echoPin, HIGH, 30000);

  // Verifica se houve leitura valida
  if (duracao == 0) {
    Serial.println("Erro ao medir o nivel da agua!");
    delay(1000);
    return;
  }

  // Calcula a distancia em centimetros
  float distancia = duracao * 0.0343 / 2;

  // Converte a distancia em porcentagem de agua
  int nivel = (int)((alturaCaixa - distancia) / alturaCaixa * 100);

  // Limita o nivel entre 0% e 100%
  nivel = constrain(nivel, 0, 100);

  // Identifica a categoria do nivel
  int estadoAtual;

  if (nivel > 70) {
    estadoAtual = 2;
  }
  else if (nivel >= 30) {
    estadoAtual = 1;
  }
  else {
    estadoAtual = 0;
  }

  // Atualiza os indicadores
  digitalWrite(ledVerde, estadoAtual == 2 ? HIGH : LOW);
  digitalWrite(ledAmarelo, estadoAtual == 1 ? HIGH : LOW);
  digitalWrite(ledVermelho, estadoAtual == 0 ? HIGH : LOW);

  // Ativa o buzzer somente quando o nivel estiver baixo
  if (estadoAtual == 0) {
    tone(buzzer, 1000);
  }
  else {
    noTone(buzzer);
  }

  // Exibe mensagens somente quando a categoria mudar
  if (estadoAtual != ultimoEstado) {

    Serial.print("Nivel da caixa d'agua: ");
    Serial.print(nivel);
    Serial.println("%");

    if (estadoAtual == 2) {
      Serial.println("Nivel alto: caixa d'agua abastecida!");
    }
    else if (estadoAtual == 1) {
      Serial.println("Nivel medio: monitoramento ativo.");
    }
    else {
      Serial.println("ALERTA: nivel baixo de agua!");
    }

    ultimoEstado = estadoAtual;
  }

  delay(1000);
}
