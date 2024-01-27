//Generated Date: Fri, 26 Jan 2024 02:56:07 GMT

#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

char _lwifi_ssid[] = "jumbo";
char _lwifi_pass[] = "0953313123";
int thingSpeakRec=0;
DHT dht11_p4(4, DHT11);

void invokeThingSpeak(const String& key, const String& p1, const String& p2, const String& p3, const String& p4, const String& p5, const String& p6, const String& p7, const String& p8)
{
  static HTTPClient client;
  client.begin("http://api.thingspeak.com/update");
  client.addHeader("Content-Type", "application/json");
  const String payload = String() + "{\"api_key\":\"" + key
                        + "\",\"field1\":\"" + p1
                        + "\",\"field2\":\"" + p2
                        + "\",\"field3\":\"" + p3
                        + "\",\"field4\":\"" + p4
                        + "\",\"field5\":\"" + p5
                        + "\",\"field6\":\"" + p6
                        + "\",\"field7\":\"" + p7
                        + "\",\"field8\":\"" + p8
                        + "\"}";
  int postCode=client.POST(payload);
  if (postCode==200)
    thingSpeakRec=client.getString().toInt();
  else
    thingSpeakRec=0;
  client.end();
}

void setup()
{
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
  invokeThingSpeak("D8VZUX68CESSH1TK", String(dht11_p4.readTemperature()), String(dht11_p4.readHumidity()), String(0), String(0), String(0), String(0), String(0), String(0));
  delay(15000);
}
