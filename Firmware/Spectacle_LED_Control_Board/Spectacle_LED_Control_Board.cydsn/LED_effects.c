#include <project.h>
#include <stdbool.h>
#include <stdlib.h>
#include "WS2811.h"
#include "led.h"
#include "LED_effects.h"

extern uint32 systemTimer;
extern uint8 fading[3];
int16 redStep[3] = {0,0,0};
int16 greenStep[3] = {0,0,0};
int16 blueStep[3] = {0,0,0};
int16 red[3] = {0,0,0};
int16 green[3] = {0,0,0};
int16 blue[3] = {0,0,0};

void setColor(uint32 color, uint8 stringID, uint8 pixel)
{
  int j;
  for (j = 0; j < pixel; j++)
  {
    StripLights_Pixel(j, stringID, color);
  }
}

void fadeString(struct led *behavior)
{
  int redStart;
  int redStop;
  int blueStart;
  int blueStop;
  int greenStart;
  int greenStop;
  int temp;
  rgbBreak(behavior->color0, &redStart, &greenStart, &blueStart);
  rgbBreak(behavior->color1, &redStop, &greenStop, &blueStop);
  if (redStart>redStop)
  {
    temp = redStart;
    redStart = redStop;
    redStop = temp;
  } 
  if (blueStart>blueStop)
  {
    temp = blueStart;
    blueStart = blueStop;
    blueStop = temp;
  } 
  if (greenStart>greenStop)
  {
    temp = greenStart;
    greenStart = greenStop;
    greenStop = temp;
  } 
  int redRange = redStop - redStart;
  int blueRange = blueStop - blueStart;
  int greenRange = greenStop - greenStart;
  if (fading[behavior->stringID] == 0)
  {
    fading[behavior->stringID] = 1;
    redStep[behavior->stringID] = redRange/16;
    blueStep[behavior->stringID] = blueRange/16;
    greenStep[behavior->stringID] = greenRange/16;
    red[behavior->stringID] = redStart;
    blue[behavior->stringID] = blueStart;
    green[behavior->stringID] = greenStart;
  }

  if (red[behavior->stringID]+redStep[behavior->stringID] >= redStop)
  {
    red[behavior->stringID] = redStop;
    redStep[behavior->stringID]*=-1;
  }
  else if (red[behavior->stringID]+redStep[behavior->stringID] <= redStart)
  {
    red[behavior->stringID] = redStart;
    redStep[behavior->stringID] *= -1;
  }
  else
  {
    red[behavior->stringID] += redStep[behavior->stringID];
  }

  if (blue[behavior->stringID]+blueStep[behavior->stringID] >= blueStop)
  {
    blue[behavior->stringID] = blueStop;
    blueStep[behavior->stringID]*=-1;
  }
  else if (blue[behavior->stringID]+blueStep[behavior->stringID] <= blueStart)
  {
    blue[behavior->stringID] = blueStart;
    blueStep[behavior->stringID] *= -1;
  }
  else
  {
    blue[behavior->stringID] += blueStep[behavior->stringID];
  }
  
  if (green[behavior->stringID]+greenStep[behavior->stringID] >= greenStop)
  {
    green[behavior->stringID] = greenStop;
    greenStep[behavior->stringID]*=-1;
  }
  else if (green[behavior->stringID]+greenStep[behavior->stringID] <= greenStart)
  {
    green[behavior->stringID] = greenStart;
    greenStep[behavior->stringID] *= -1;
  }
  else
  {
    green[behavior->stringID] += greenStep[behavior->stringID];
  }
  uint32 color = rgbMake(blue[behavior->stringID], green[behavior->stringID], 
                         red[behavior->stringID]);
  setColor(color, behavior->stringID, behavior->stringLen);
}

void rainbow(struct led *behavior)
{
  int i = 0;
  for (i=0; i<behavior->stringLen; i++)
  {
    StripLights_Pixel(i, behavior->stringID, wheel((behavior->iteration + i) & 255));
  }
    behavior->iteration++;
  
}

void theaterchase(struct led *behavior)
{
  int i;
  setColor(0, behavior->stringID, behavior->stringLen);
  for (i = behavior->iteration; i < behavior->stringLen; i+=3)
  {
    StripLights_Pixel(i, behavior->stringID, behavior->color0);
  }
  if (++behavior->iteration > 2) 
  {
    behavior->iteration = 0;
  }
}

void scan(struct led *behavior)
{
  int red = (behavior->color0&RED_MASK)>>RED_SHIFT;
  int green = (behavior->color0&GREEN_MASK)>>GREEN_SHIFT;
  int blue = (behavior->color0&BLUE_MASK)>>BLUE_SHIFT;
  uint32 halfcolor = (red/4)<<RED_SHIFT | (green/4)<<GREEN_SHIFT | \
                     (blue/4)<<BLUE_SHIFT;
  uint32 color = behavior->color0;
  setColor(0, behavior->stringID, behavior->stringLen);
  if (behavior->iteration == 0)
  {
    StripLights_Pixel(0, behavior->stringID, color);
    StripLights_Pixel(1, behavior->stringID, halfcolor);
    behavior->direction = 1;
  }
  else if (behavior->iteration == behavior->stringLen - 1)
  {
    StripLights_Pixel(behavior->stringLen-1, behavior->stringID, color);
    StripLights_Pixel(behavior->stringLen-2, behavior->stringID, halfcolor);
    behavior->direction = -1;
  }
  else
  {
    StripLights_Pixel(behavior->iteration, behavior->stringID, color);
    StripLights_Pixel(behavior->iteration-1, behavior->stringID, halfcolor);
    StripLights_Pixel(behavior->iteration+1, behavior->stringID, halfcolor);
  }
  behavior->iteration += behavior->direction;

}

void twinkle(struct led *behavior)
{
  int index = behavior->iteration;
  int8 twinkleStep=behavior->twinkleStep;
  int8 twinkleStepMax = behavior->twinkleStepMax;
  int redMax=0;
  int blueMax=0;
  int greenMax=0;
  if (behavior->inProcess == 0)
  {
    behavior->inProcess = 1;
    srand(systemTimer);
    behavior->twinkleStepMax = (rand() % 4)+5;
    twinkleStepMax = behavior->twinkleStepMax;  
    twinkleStep = 0;
    behavior->red = 0;
    behavior->blue = 0;
    behavior->green = 0;
    index = rand() % behavior->stringLen;
  }
  rgbBreak(behavior->color0, &redMax, &greenMax, &blueMax);
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
    behavior->red += redStep;
    behavior->blue += blueStep;
    behavior->green += greenStep;
  }
  if (behavior->red > 255) behavior->red = 255;
  if (behavior->blue > 255) behavior->blue = 255;
  if (behavior->green > 255) behavior->green = 255;
  if (behavior->red < 0) behavior->red = 0;
  if (behavior->blue < 0) behavior->blue = 0;
  if (behavior->green < 0) behavior->green = 0;

  setColor(0, behavior->stringID, behavior->stringLen);
  StripLights_Pixel(index, behavior->stringID, rgbMake(behavior->red, 
                                                       behavior->green, 
                                                       behavior->blue));
  if (twinkleStep == 2*twinkleStepMax)
  {
    behavior->inProcess = false;
    setColor(0, behavior->stringID, behavior->stringLen);
  }
  behavior->iteration = index;
  behavior->twinkleStep = twinkleStep;
}

/*
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

