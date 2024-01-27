/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 25 Jan 2024 13:06:29 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


void setup()
{

  pinMode(4, INPUT);
  Serial.begin(9600);

}


void loop()
{
  Serial.print(digitalRead(4));
  delay(500);
}