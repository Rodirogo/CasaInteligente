#include <Arduino.h>

// Definicao dos pinos
const int sensorUmidade = A0;
const int bombaAgua = 8;

// Limite de umidade para ativar a irrigacao
const int limiteUmidade = 40;

// Armazena o estado da bomba
bool bombaLigada = false;

// Armazena o ultimo estado de umidade
int ultimoEstado = -1;

void setup() {
  pinMode(sensorUmidade, INPUT);
  pinMode(bombaAgua, OUTPUT);

  digitalWrite(bombaAgua, LOW);

  Serial.begin(9600);

  Serial.println("Sistema de irrigacao iniciado!");
}

void loop() {
  // Leitura do sensor de umidade
  int leitura = analogRead(sensorUmidade);

  // Converte a leitura analogica em porcentagem
  int umidade = map(leitura, 0, 1023, 100, 0);

  // Exibe a umidade somente quando mudar
  if (umidade != ultimoEstado) {
    Serial.print("Umidade do solo: ");
    Serial.print(umidade);
    Serial.println("%");

    ultimoEstado = umidade;
  }

  // Liga a bomba quando a umidade estiver abaixo de 40%
  if (umidade < limiteUmidade && !bombaLigada) {
    digitalWrite(bombaAgua, HIGH);
    bombaLigada = true;

    Serial.println("Solo seco: irrigacao ativada!");
  }

  // Desliga a bomba quando a umidade atingir 40% ou mais
  else if (umidade >= limiteUmidade && bombaLigada) {
    digitalWrite(bombaAgua, LOW);
    bombaLigada = false;

    Serial.println("Umidade adequada: irrigacao desligada!");
  }

  delay(1000);
}
