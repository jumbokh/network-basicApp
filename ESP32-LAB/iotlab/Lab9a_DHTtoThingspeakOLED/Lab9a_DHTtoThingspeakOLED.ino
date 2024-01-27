//Generated Date: Fri, 26 Jan 2024 03:12:01 GMT

#include "Wire.h"
#include "U8g2lib.h"
#include <WiFi.h>
#include <DHT.h>
#include <HTTPClient.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int clock_center_x=64;
int clock_center_y=32;
char _lwifi_ssid[] = "jumbo";
char _lwifi_pass[] = "0953313123";
DHT dht11_p4(4, DHT11);
int thingSpeakRec=0;

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
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);

  u8g2.setFont(u8g2_font_unifont_t_chinese1);
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
  u8g2.firstPage();
  do {
    u8g2.setCursor(15, 10);
    u8g2.print(String(String("溫度:")+String(dht11_p4.readTemperature())+String(" C")).c_str());
    u8g2.setCursor(15, 30);
    u8g2.print(String(String("溼度:")+String(dht11_p4.readHumidity())+String("%")).c_str());

    u8g2.sendBuffer();
  } while (u8g2.nextPage());
  invokeThingSpeak("D8VZUX68CESSH1TK", String(dht11_p4.readTemperature()), String(dht11_p4.readHumidity()), String(0), String(0), String(0), String(0), String(0), String(0));
  delay(15000);
}
