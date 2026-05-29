#include <WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"

// WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

// DHT
DHTesp dhtSensor;

#define DHT_PIN 15
#define LED_PIN 2

// ---------------- WIFI ----------------

void setup_wifi() {

  delay(10);

  Serial.println();
  Serial.print("Conectando ao WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado!");
}

// ---------------- MQTT ----------------

void reconnect() {

  while (!client.connected()) {

    Serial.print("Conectando MQTT...");

    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {

      Serial.println(" conectado!");

      client.publish(
        "projeto/eric/status",
        "ESP32 conectado"
      );

    } else {

      Serial.print(" falhou");
      delay(5000);
    }
  }
}

// ---------------- SETUP ----------------

void setup() {

  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  setup_wifi();

  client.setServer(mqtt_server, 1883);
}

// ---------------- LOOP ----------------

void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  TempAndHumidity data = dhtSensor.getTempAndHumidity();

  float temperatura = data.temperature;
  float umidade = data.humidity;

  Serial.println("Temperatura: " + String(temperatura));
  Serial.println("Umidade: " + String(umidade));

  // Converter float para char
  char tempString[8];
  dtostrf(temperatura, 1, 2, tempString);

  char umidString[8];
  dtostrf(umidade, 1, 2, umidString);

  // Envia MQTT
  client.publish("projeto/eric/temperatura", tempString);
  client.publish("projeto/eric/umidade", umidString);

  // Controle LED
  if (temperatura > 30) {

    digitalWrite(LED_PIN, HIGH);

    client.publish(
      "projeto/eric/led",
      "Ligado"
    );

  } else {

    digitalWrite(LED_PIN, LOW);

    client.publish(
      "projeto/eric/led",
      "Desligado"
    );
  }

  delay(3000);
}