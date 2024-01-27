/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Thu, 25 Jan 2024 12:59:00 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


String matrixString = "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

int MatrixLed_marquee_time = 500;

int MatrixLed_marquee_rotate = 0;

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, 32, NEO_GRB + NEO_KHZ800);

String strTemp_ = "";

int HextoRGB(char val) {
  String hex ="0123456789abcdef";
  return hex.indexOf(val);
}

void MatrixLedOne(int i, String color) {
  color.replace("#","");
  matrixString[i*6+0] = color[0];
  matrixString[i*6+1] = color[1];
  matrixString[i*6+2] = color[2];
  matrixString[i*6+3] = color[3];
  matrixString[i*6+4] = color[4];
  matrixString[i*6+5] = color[5];
  int R,G,B;
  R = (HextoRGB(color[0])*16+HextoRGB(color[1]));
  G = (HextoRGB(color[2])*16+HextoRGB(color[3]));
  B = (HextoRGB(color[4])*16+HextoRGB(color[5]));
  pixels.setPixelColor(i, pixels.Color(R, G, B));
  pixels.show();
}

void MatrixLed(String color) {
  color.replace("#","");
  matrixString = color;
  int R,G,B;
  int range;
  range = color.length()/6;
  for (int i=0;i<range;i++) {
    R = (HextoRGB(color[i*6])*16+HextoRGB(color[i*6+1]));
    G = (HextoRGB(color[i*6+2])*16+HextoRGB(color[i*6+3]));
    B = (HextoRGB(color[i*6+4])*16+HextoRGB(color[i*6+5]));
    pixels.setPixelColor(i, pixels.Color(R, G, B));
  }
  pixels.show();
}

void setup()
{
  pixels.begin();
  pixels.show();


}


void loop()
{
  MatrixLedOne((1-1),"ff0000");
  delay(1000);
  MatrixLedOne((1-1),"33cc00");
  delay(1000);
  MatrixLedOne((1-1),"000099");
  delay(1000);
  MatrixLed("000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
  delay(3000);
}