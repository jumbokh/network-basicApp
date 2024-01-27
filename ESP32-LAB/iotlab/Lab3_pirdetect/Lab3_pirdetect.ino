/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 25 Jan 2024 13:10:58 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


void setup()
{

  pinMode(4, INPUT);
  Serial.begin(9600);

  pinMode(2, OUTPUT);
  pinMode(15, OUTPUT);
}


void loop()
{
  Serial.print(digitalRead(4));
  if (digitalRead(4) == true) {
    digitalWrite(2, HIGH);
    digitalWrite(15, LOW);
    delay(3000);

  } else {
    digitalWrite(2, LOW);
    digitalWrite(15, HIGH);

  }
  delay(500);
}