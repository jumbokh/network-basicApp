//Generated Date: Fri, 26 Jan 2024 04:12:42 GMT

#include "Wire.h"
#include "U8g2lib.h"
#include <WiFi.h>
#include <DHT.h>
#include <WiFiClientSecure.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int clock_center_x=64;
int clock_center_y=32;
char _lwifi_ssid[] = "jumbo";
char _lwifi_pass[] = "0953313123";
DHT dht11_p4(4, DHT11);

String LineNotify(String token, String request) {
  String getAll="", getBody="";
  request.replace("%","%25");
  request.replace(" ","%20");
  request.replace("&","%20");
  request.replace("#","%20");
  request.replace("\"","%22");
  request.replace("\n","%0D%0A");
  request.replace("%20stickerPackageId","&stickerPackageId");
  request.replace("%20stickerId","&stickerId");
  request.replace("%20imageFullsize","&imageFullsize");
  request.replace("%20imageThumbnail","&imageThumbnail");
  WiFiClientSecure client_tcp;
  client_tcp.setInsecure();
  if (client_tcp.connect("notify-api.line.me", 443)) {
    client_tcp.println("POST /api/notify HTTP/1.1");
    client_tcp.println("Connection: close");
    client_tcp.println("Host: notify-api.line.me");
    client_tcp.println("User-Agent: ESp8266/1.0");
    client_tcp.println("Authorization: Bearer " + token);
    client_tcp.println("Content-Type: application/x-www-form-urlencoded");
    client_tcp.println("Content-Length: " + String(request.length()));
    client_tcp.println();
    client_tcp.println(request);
    client_tcp.println();
    boolean state = false;
    long startTime = millis();
    while ((startTime + 3000) > millis()) {
      while (client_tcp.available()) {
        char c = client_tcp.read();
        if (c == '\n') {
          if (getAll.length()==0) state=true;
           getAll = "";
        }
        else if (c != '\r')
          getAll += String(c);
          if (state==true) getBody += String(c);
          startTime = millis();
        }
        if (getBody.length()!= 0) break;
      }
      client_tcp.stop();
      Serial.println(getBody);
  }
  else {
    getBody="Connected tonotify-api.line.me failed.";
    Serial.println("Connected to notify-api.line.me failed.");
  }
  return getBody;
}

void setup()
{
  Serial.begin(9600);

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
  Serial.println(WiFi.localIP().toString());
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
  if (dht11_p4.readTemperature() >= 28 || dht11_p4.readHumidity() >= 60) {
    LineNotify("HkZ5L7iJHxlzPBPL4HPeHlOfW7VySSssVLChYSvBIha", "message="+String((String("發現環境異常，請派員查看。現在狀態:")+String("\n")+String("溫度:")+String(dht11_p4.readTemperature())+String("\n")+String("溼度:")+String(dht11_p4.readHumidity()))));
  }
  delay(10000);
}
