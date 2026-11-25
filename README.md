# Casa-Inteligente
Casa inteligente simulada: 6 automações embarcadas em Arduino Uno (C++), simuladas no Wokwi com PlatformIO. Trabalho de Sistemas Embarcados, UVA.


Trabalho opcional da A2 de Sistemas Embarcados, Universidade Veiga de Almeida (Prof. Caio Silva Azeredo).

**Autor:** Rodrigo Manhães Cosenza

## Automações

| Pasta | Automação | Entrada | Saída |
|---|---|---|---|
| `Automação1_Iluminação` | Luz acesa por presença | Sensor PIR | LED |
| `Automação2_Arcondicionado` | Ar-condicionado por temperatura | DHT22 | LED |
| `Automação3_AlarmePorta` | Alarme de porta aberta | Chave deslizante | Buzzer |
| `Automação4_Irrigação` | Irrigação por umidade do solo | Potenciômetro | LED (bomba) |
| `Automação5_NivelCaixaAgua` | Nível da caixa d'água | HC-SR04 | 3 LEDs e buzzer |
| `Automação6_DetectorGas` | Detector de gás | MQ-2 | LED e buzzer |

Cada pasta é um projeto PlatformIO independente (`src/main.cpp`, `platformio.ini`, `diagram.json`, `wokwi.toml`).

## Como executar

1. Instale o Visual Studio Code e as extensões **PlatformIO IDE** e **Wokwi Simulator**.
2. Clone este repositório.
3. No VS Code, abra a pasta de **uma automação** (não a pasta raiz).
4. Compile com *PlatformIO: Build* (ou `pio run`). Isso gera `.pio/build/uno/firmware.hex`, usado pelo `wokwi.toml`.
5. Pressione `F1` e escolha *Wokwi: Start Simulator*. Se pedir, solicite a licença gratuita (*Wokwi: Request a new License*).
6. Interaja com o componente: botão *Simulate motion* (PIR), controles do DHT22, chave, potenciômetro, distância do HC-SR04 ou ppm do MQ-2. As mensagens aparecem no terminal.
