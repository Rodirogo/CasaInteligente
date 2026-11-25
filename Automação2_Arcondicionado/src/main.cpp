
#include <Arduino.h>
#include <DHT.h>

// Definicao dos pinos
const int pinoDHT = 2;
const int arCondicionado = 13;

// Configuracao do sensor DHT22
#define DHTTYPE DHT22
DHT dht(pinoDHT, DHTTYPE);

// Temperatura para ligar o ar-condicionado
const float temperaturaLimite = 26.0;

// Estado do ar-condicionado
bool arLigado = false;

// Armazena a ultima temperatura exibida
float ultimaTemperatura = -100;

void setup() {
  pinMode(arCondicionado, OUTPUT);
  digitalWrite(arCondicionado, LOW);

  Serial.begin(9600);
  dht.begin();

  Serial.println("Sistema de ar-condicionado iniciado!");
}

void loop() {
  float temperatura = dht.readTemperature();

  if (isnan(temperatura)) {
    Serial.println("Erro ao ler o sensor DHT22!");
    delay(2000);
    return;
  }

  // Exibe a temperatura somente se variar pelo menos 1 grau
  if (abs(temperatura - ultimaTemperatura) >= 1.0) {
    Serial.print("Temperatura atual: ");
    Serial.print(temperatura);
    Serial.println(" C");

    ultimaTemperatura = temperatura;
  }

  // Liga o ar-condicionado acima de 26 graus
  if (temperatura > temperaturaLimite && !arLigado) {
    digitalWrite(arCondicionado, HIGH);
    arLigado = true;

    Serial.println("Temperatura alta: ar-condicionado ligado!");
  }

  // Desliga o ar-condicionado em 26 graus ou menos
  else if (temperatura <= temperaturaLimite && arLigado) {
    digitalWrite(arCondicionado, LOW);
    arLigado = false;

    Serial.println("Temperatura adequada: ar-condicionado desligado!");
  }

  delay(2000);
}
