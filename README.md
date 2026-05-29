# projeto-iot-esp32-mqtt
Projeto de monitoramento de temperatura e umidade utilizando ESP32, DHT22 e protocolo MQTT.

# Sistema de Monitoramento com ESP32 e MQTT

Projeto desenvolvido para a disciplina de Objetos Inteligentes Conectados.

## Descrição

O projeto consiste em um sistema de monitoramento de temperatura e umidade utilizando ESP32, sensor DHT22 e protocolo MQTT.

O sistema realiza a leitura das condições do ambiente e aciona automaticamente um LED quando a temperatura ultrapassa 30°C.

Todo o desenvolvimento foi realizado utilizando o simulador Wokwi.

---

## Componentes utilizados

- ESP32
- Sensor DHT22
- LED
- Protoboard virtual
- Broker MQTT HiveMQ

---

## Tecnologias utilizadas

- Arduino IDE
- MQTT
- HiveMQ
- Wokwi Simulator
- Linguagem C/C++

---

## Funcionalidades

- Leitura de temperatura
- Leitura de umidade
- Comunicação MQTT
- Acionamento automático de LED
- Monitoramento em tempo real

---

## Estrutura do projeto

O ESP32 realiza a leitura dos dados do sensor DHT22 e envia as informações para tópicos MQTT utilizando conexão Wi-Fi.

Quando a temperatura ultrapassa 30°C, o LED é acionado automaticamente.

---

## Simulação

O projeto foi desenvolvido utilizando o simulador Wokwi devido à indisponibilidade de hardware físico.

---

## Funcionamento e reprodução do projeto

O sistema funciona realizando a leitura da temperatura e da umidade do ambiente por meio do sensor DHT22 conectado ao ESP32.

Os dados coletados são processados pelo microcontrolador e enviados utilizando o protocolo MQTT através de conexão Wi-Fi.

Quando a temperatura ultrapassa 30°C, o sistema aciona automaticamente um LED como forma de alerta visual.

Para reproduzir o projeto, é necessário:

1. Acessar o simulador Wokwi;
2. Criar um projeto utilizando ESP32;
3. Adicionar os componentes DHT22 e LED;
4. Inserir o código-fonte disponível neste repositório;
5. Instalar as bibliotecas WiFi, PubSubClient e DHTesp;
6. Iniciar a simulação no Wokwi.

Após iniciar a simulação, o sistema começará automaticamente a monitorar as condições do ambiente simulado.

---

## Autor

Eric Tomaz dos Santos Silva
