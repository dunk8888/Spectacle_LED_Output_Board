#include <project.h>
#include <stdbool.h>
#include <stdlib.h>
#include "WS2811.h"
#include "led.h"
#include "LED_effects.h"

extern uint32 buffer[3][60];
extern uint32 systemTimer;
extern int stringLen[3];
bool fading = false;

void setColor(struct led *behavior)
{
  int i = 0;
  for (i = 0; i < behavior->stringLen; i++)
  {
    buffer[behavior->stringID][i] = behavior->color0;
  }
}

void setPixel(struct led *behavior)
{
  int i = 0;
  for (i = 0; i < behavior->pixel; i++)
  {
    buffer[behavior->stringID][i] = 0;
  }
  buffer[behavior->stringID][i] = behavior->color0;
  for (i = behavior->pixel+1; i< behavior->stringLen; i++)
  {
    buffer[behavior->stringID][i] = 0;
  }
}
/*
void fadeString(struct led *behavior)
{
  static int red;
  static int blue;
  static int green;
  static int redStep;
  static int blueStep;
  static int greenStep;
  static int redStart;
  static int redStop;
  static int blueStart;
  static int blueStop;
  static int greenStart;
  static int greenStop;
  if (fading == false)
  {
    fading = true;
    rgbBreak(color0, &redStart, &greenStart, &blueStart);
    red = redStart;
    blue = blueStart;
    green = greenStart;
    rgbBreak(color1, &redStop, &greenStop, &blueStop);
    int redRange = redStop - redStart;
    int blueRange = blueStop - blueStart;
    int greenRange = greenStop - greenStart;
    redStep = redRange/16;
    blueStep = blueRange/16;
    greenStep = greenRange/16;

  }
  uint32 color = rgbMake(red, green, blue);
  setColor(color, stringID);

  if (red+redStep > redStop)
  {
    red = redStop;
    redStep*=-1;
  }
  else if (red+redStep < redStart)
  {
    red = redStart;
    redStep *= -1;
  }
  else
  {
    red += redStep;
  }

  if (blue+blueStep > blueStop)
  {
    blue = blueStop;
    blueStep*=-1;
  }
  else if (blue+blueStep < blueStart)
  {
    blue = blueStart;
    blueStep *= -1;
  }
  else
  {
    blue += blueStep;
  }
  
  if (green+greenStep > greenStop)
  {
    green = greenStop;
    greenStep*=-1;
  }
  else if (green+greenStep < greenStart)
  {
    green = greenStart;
    greenStep *= -1;
  }
  else
  {
    green += greenStep;
  }
}

void partialFill(struct led *behavior)
{
  int i = 0;
  for (i = 0; i <= pixel; i++)
  {
    buffer[stringID][i] = color;
  }
  for (i = pixel; i< stringLen[stringID]; i++)
  {
    buffer[stringID][i] = 0;
  }
}

void rainbow(struct led *behavior)
{
  int i = 0;
  for (i=0; i<stringLen[stringID]; i++)
  {
    buffer[stringID][i] = wheel((iteration + i) & 255);
  }
  
}

void theaterchase(struct led *behavior)
{
  static int index = 0;
  int i;
  setColor(0, stringID);
  for (i = index; i < stringLen[stringID]; i+=3)
  {
    buffer[stringID][i] = color;
  }
  if (++index > 2) 
  {
    index = 0;
  }
}

void scan(struct led *behavior)
{
  static int index = 0;
  static int scanDirection = 1;
  int red = (color&RED_MASK)>>RED_SHIFT;
  int green = (color&GREEN_MASK)>>GREEN_SHIFT;
  int blue = (color&BLUE_MASK)>>BLUE_SHIFT;
  uint32 halfColor = (red/4)<<RED_SHIFT | (green/4)<<GREEN_SHIFT | \
                     (blue/4)<<BLUE_SHIFT;
  setColor(0, stringID);
  if (index == 0)
  {
    buffer[stringID][0] = color;
    buffer[stringID][1] = halfColor;
    scanDirection = 1;
  }
  else if (index == stringLen[stringID] - 1)
  {
    buffer[stringID][index] = color;
    buffer[stringID][index-1] = halfColor;
    scanDirection = -1;
  }
  else
  {
    buffer[stringID][index-1] = halfColor;
    buffer[stringID][index] = color;
    buffer[stringID][index+1] = halfColor;
  }
  index+=scanDirection;

}

bool twinkle(struct led *behavior)
{
  static int index=0;
  static int twinkleStep=0;
  static int twinkleStepMax=0;
  static int redMax=0;
  static int blueMax=0;
  static int greenMax=0;
  static int red=0;
  static int blue=0;
  static int green=0;
  static bool twinkling=false;
  if (!twinkling)
  {
    twinkling = true;
    srand(systemTimer);
    twinkleStepMax = (rand() % 4)+2;
    twinkleStep = 0;
    red = 0;
    blue = 0;
    green = 0;
    rgbBreak(color, &redMax, &greenMax, &blueMax);
    index = rand() % stringLen[stringID];
  }
  int redStep = redMax/twinkleStepMax;
  int blueStep = blueMax/twinkleStepMax;
  int greenStep = greenMax/twinkleStepMax;
  if (twinkleStep >= twinkleStepMax-1)
  {
    redStep *= -1;
    blueStep *= -1;
    greenStep *= -1;
  }
  if (twinkleStep++ < 2*twinkleStepMax)
  {
    red += redStep;
    blue += blueStep;
    green += greenStep;
  }
  if (red > 255) red = 255;
  if (blue > 255) blue = 255;
  if (green > 255) green = 255;
  if (red < 0) red = 0;
  if (blue < 0) blue = 0;
  if (green < 0) green = 0;

  setColor(0,stringID);
  buffer[stringID][index] = rgbMake(red, green, blue);
  if (twinkleStep == 2*twinkleStepMax)
  {
    twinkling = false;
    setColor(0, stringID);
    return false;
  }
  return true;
}

bool lightning(struct led *behavior)
{
  static int strikeStep=0;
  static int strikeStepMax=0;
  static uint32 colorCache;
  static bool twinkling=false;
  if (!twinkling)
  {
    twinkling = true;
    srand(systemTimer);
    strikeStepMax = (rand() % 6)+3;
    colorCache = color;
    strikeStep = 0;
  }
  if ((rand() % 2) == 1)
  {
    setColor(colorCache, stringID);
  }
  else
  {
    setColor(0, stringID);
  }
  if (strikeStep++ == 2*strikeStepMax)
  {
    twinkling = false;
    setColor(0, stringID);
    return false;
  }
  return true;
}
*/
// This function was lifted from the Adafruit NeoPixel library example. It
//  calculates a color wheel transition from red thru green and blue back to
//  red. Can be used for multiple effects.
uint32 wheel(uint8 wheelPos)
{
  wheelPos = 255 - wheelPos;
  if (wheelPos < 85)
  {
    return (255 - wheelPos*3)<<RED_SHIFT | (wheelPos*3)<<BLUE_SHIFT;
  }
  if (wheelPos < 170)
  {
    wheelPos -= 85;
    return (wheelPos * 3)<<GREEN_SHIFT | (255 - wheelPos*3)<<BLUE_SHIFT;
  }
  wheelPos -= 170;
  return (wheelPos*3)<<RED_SHIFT | (255-wheelPos*3)<<GREEN_SHIFT;
}

void rgbBreak(uint32 color, int *red, int *green, int *blue)
{
  *red = (color & RED_MASK)>>RED_SHIFT;
  *blue = (color & BLUE_MASK)>>BLUE_SHIFT;
  *green = (color & GREEN_MASK)>>GREEN_SHIFT;
}

uint32 rgbMake(int red, int green, int blue)
{
  return red<<RED_SHIFT | green<<GREEN_SHIFT | blue<<BLUE_SHIFT;
}
