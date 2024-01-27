//Generated Date: Fri, 26 Jan 2024 05:51:13 GMT

#include <WiFi.h>
#include <PubSubClient.h>
#define MQTT_USER ""
#define MQTT_PASSWORD ""
#include <DHT.h>

char _lwifi_ssid[] = "jumbo";
char _lwifi_pass[] = "0953313123";
const char* mqtt_server = "mqttgo.io";
const unsigned int mqtt_port = 1883;
WiFiClient espClient;
PubSubClient mqtt_client(espClient);
String mqtt_data = "";

void mqtt_sendText(String topic, String text) {
    String clientId = "";
    if (mqtt_client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) {
      mqtt_client.publish(topic.c_str(), text.c_str());
    }
}

void reconnect() {
  while (!mqtt_client.connected()) {
    String mqtt_clientId = "";
    if (mqtt_client.connect(mqtt_clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) {
        } else {
      delay(5000);
    }
  }
}

DHT dht11_p4(4, DHT11);

void setup()
{
  randomSeed(micros());
  mqtt_client.setServer(mqtt_server,mqtt_port);
  mqtt_client.setCallback(callback);
  //mqtt_client.setBufferSize(1024);

  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(_lwifi_ssid, _lwifi_pass);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  delay(300);
  dht11_p4.begin();
}

void loop()
{
  mqtt_sendText("jumbo/room/temp", String(dht11_p4.readTemperature()));
  mqtt_sendText("jumbo/room/humi", String(dht11_p4.readHumidity()));
  delay(1000);
}

void callback(char* topic, byte* payload, unsigned int length) {
  mqtt_data = "";
  for (int ci = 0; ci < length; ci++) {
    char c = payload[ci];
    mqtt_data+=c;
  }
}
