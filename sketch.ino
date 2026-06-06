#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

// Configurações do Sensor DHT22 e LED (Baseado na sua Figura 5)
#define DHTPIN 15     // Pino de dados do DHT22 (ajuste se estiver em outro)
#define DHTTYPE DHT22
#define LED_PIN 2     // Pino do LED

DHT dht(DHTPIN, DHTTYPE);

// Configurações do Wi-Fi do Wokwi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Configurações do Broker MQTT (Usando o EMQX Público que roda liso no Wokwi)
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

// Tópicos ÚNICOS para o seu projeto (mudei para incluir seu RA/Nome e evitar interferência)
const char* topic_temp = "mackenzie/eric10441410/temperatura";
const char* topic_status = "mackenzie/eric10441410/status";

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando em ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Wi-Fi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    // Cria um ID de cliente único
    String clientId = "ESP32Client-Eric-";
    clientId += String(random(0, 0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado ao Broker!");
      client.publish(topic_status, "Sistema Inicializado");
    } else {
      Serial.print("Falhou, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  dht.begin();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  // Faz a leitura e o envio a cada 2 segundos
  if (now - lastMsg > 2000) {
    lastMsg = now;

    float t = dht.readTemperature();
    float h = dht.readHumidity();

    if (isnan(t) || isnan(h)) {
      Serial.println("Falha ao ler o sensor DHT22!");
      return;
    }

    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.print(" *C | Umidade: ");
    Serial.print(h);
    Serial.println(" %");

    // Lógica do LED e Envio das Mensagens MQTT
    if (t > 30.0) {
      digitalWrite(LED_PIN, HIGH);
      client.publish(topic_status, "ALERTA: LED ACESO - Temp acima de 30C");
    } else {
      digitalWrite(LED_PIN, LOW);
      client.publish(topic_status, "STATUS: Normal - LED Desligado");
    }

    // Envia o valor exato da temperatura
    char tempString[8];
    dtostrf(t, 1, 2, tempString);
    client.publish(topic_temp, tempString);
  }
}
