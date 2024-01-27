/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 25 Jan 2024 13:52:18 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */
#include <DHT.h>

DHT dht11_p4(4, DHT11);

void setup()
{

  dht11_p4.begin();
  Serial.begin(9600);

}


void loop()
{
  Serial.println(dht11_p4.readTemperature());
  Serial.println(dht11_p4.readHumidity());
  delay(1000);
}