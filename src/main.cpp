#include <Arduino.h>
#include <secrets.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define LOG(...) Serial.printf(__VA_ARGS__)

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void mqttCallback(char *topic, byte *payload, unsigned int length)
{

  String topicString = String(topic);
  String payloadString = "";
  for (uint i = 0; i < length; i++)
    payloadString += (char)payload[i];

  LOG("Message arrived in topic: %s and payload %s\n", topicString.c_str(), payloadString.c_str());
  LOG("-----------------------\n");
  //  mqttClient.publish("esp/test", "received something");
}

void mqttReconnect()
{
  while (!mqttClient.connected())
  {
    LOG("Connecting to MQTT server %s as client %s...\n", MQTT_SERVER, MQTT_CLIENT_ID);
    if (mqttClient.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD))
    {
      LOG("connected\n");
    }
    else
    {
      LOG("failed with state %i\n", mqttClient.state());
      delay(2000);
    }

    mqttClient.subscribe("esp/test");
  }
}

void setup()
{
  Serial.begin(115200);

  // Setup Wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    LOG("Connecting to WiFi..\n");
  }
  LOG("Wifi connected. IP = %s\n", WiFi.localIP().toString().c_str());

  // Setup MQTT
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(mqttCallback);
  mqttReconnect();
  mqttClient.publish("esp/test", "hello");
}

void loop()
{
  mqttReconnect();
  mqttClient.loop();
}