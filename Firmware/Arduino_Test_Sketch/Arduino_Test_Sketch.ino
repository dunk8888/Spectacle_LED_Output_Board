#include <Wire.h>

enum {SET_COLOR, SET_PIXEL, FADE_STRING, PARTIAL_FILL, RAINBOW,
      THEATER_CHASE, SCAN, TWINKLE, LIGHTNING};

void setup() 
{
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Hello, world!");
}

void loop() 
{
  byte red = map(analogRead(A0), 0, 1024, 0, 255);
  byte green = map(analogRead(A1), 0, 1024, 0, 255);
  byte blue = map(analogRead(A2), 0, 1024, 0, 255);
  if (digitalRead(2) != HIGH)
  {
    sendCmd(0, SET_COLOR, 1, red, green, blue, 0, 100);
    Serial.println("Set");
    delay(50);
    while(digitalRead(2) == LOW);
  }
  if (digitalRead(3) != HIGH)
  {
    sendCmd(0, FADE_STRING, 1, red, green, blue, 0, 100);
    Serial.println("Fade");
    delay(50);
    while(digitalRead(3) == LOW);
  }
  if (digitalRead(4) != HIGH)
  {
    sendCmd(0, RAINBOW, 1, red, green, blue, 0, 100);
    Serial.println("Rainbow");
    delay(50);
    while(digitalRead(4) == LOW);
  }
  if (digitalRead(5) != HIGH)
  {
    sendCmd(0, SCAN, 1, red, green, blue, 0, 100);
    Serial.println("Scan");
    delay(50);
    while(digitalRead(5) == LOW);
  }
  if (digitalRead(6) != HIGH)
  {
    sendCmd(0, TWINKLE, 1, red, green, blue, 5, 100);
    Serial.println("Twinkle");
    delay(50);
    while(digitalRead(6) == LOW);
  }
}

void sendCmd(byte change, byte mode, byte active,
             byte red, byte green, byte blue, byte random0,
             uint32_t delay0)
{
  Wire.beginTransmission(0x0a);
  Wire.write(0);
  Wire.write(change);
  Wire.write(mode);
  Wire.write(active);
  Wire.write(red);
  Wire.write(green);
  Wire.write(blue);
  Wire.write(random0);
  Wire.write((uint8_t*)&delay0, 4);
  Wire.endTransmission();
}

