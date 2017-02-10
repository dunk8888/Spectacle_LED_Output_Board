/****************************************************************************
LED_effects.c
LED effects code file
Mike Hord @ SparkFun Electronics
24 Jan 2017
https://github.com/sparkfun/Spectacle_LED_Output_Board

Defines all of the functions which implement the various LED functions.

Development environment specifics:
Developed in PSoC Creator 4.0

This code is beerware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!
****************************************************************************/

#include <project.h>
#include <stdio.h>
#include <stdlib.h>
#include "WS2811.h"
#include "led.h"
#include "LED_effects.h"

extern uint32 systemTimer;
extern uint8 fading[3];
float redStep[3] = {0,0,0};
float greenStep[3] = {0,0,0};
float blueStep[3] = {0,0,0};
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
  rgbBreak(behavior->color0, &redStart, &greenStart, &blueStart);
  rgbBreak(behavior->color1, &redStop, &greenStop, &blueStop);
  
  redStep[behavior->stringID] = (redStop - redStart)/16;
  greenStep[behavior->stringID] = (greenStop - greenStart)/16;
  blueStep[behavior->stringID] = (blueStop - blueStart)/16;

  if (behavior->fading == 0)
  {
    behavior->iteration = 0;
    behavior->direction = 1;
    behavior->fading = 1;
  }
  
  behavior->iteration += behavior->direction;
  
  if (behavior->iteration == 17 || behavior->iteration == 0)
  {
    behavior->direction *= -1;
  }
  red[behavior->stringID] = (int16)(redStart + behavior->iteration*redStep[behavior->stringID]);
  green[behavior->stringID] = (int16)(greenStart + behavior->iteration*greenStep[behavior->stringID]);
  blue[behavior->stringID] = (int16)(blueStart + behavior->iteration*blueStep[behavior->stringID]);
  //char buffer[64];
  //sprintf(buffer, "Iter: %ld r%d g%d b%d\n", behavior->iteration, red[behavior->stringID], green[behavior->stringID], blue[behavior->stringID]);
  //UART_UartPutString(buffer);
  if (red[behavior->stringID] < 0) red[behavior->stringID] = 0;
  if (red[behavior->stringID] > 255) red[behavior->stringID] = 255;
  if (green[behavior->stringID] < 0) green[behavior->stringID] = 0;
  if (green[behavior->stringID] > 255) green[behavior->stringID] = 255;
  if (blue[behavior->stringID] < 0) blue[behavior->stringID] = 0;
  if (blue[behavior->stringID] > 255) blue[behavior->stringID] = 255;
  
  uint32 color = rgbMake(red[behavior->stringID], green[behavior->stringID], 
                         blue[behavior->stringID]);
  
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
  uint8 index = behavior->iteration;
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
    behavior->iteration = index;
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
    behavior->inProcess = 0;
    behavior->stepCntr = 0;
    setColor(0, behavior->stringID, behavior->stringLen);
  }
  behavior->twinkleStep = twinkleStep;
}


void lightning(struct led *behavior)
{
  if (behavior->inProcess == 0)
  {
    behavior->inProcess = 1;
    srand(systemTimer);
    behavior->twinkleStepMax = (rand() % 6)+3;
    behavior->twinkleStep = 0;
  }
  if ((rand() % 2) == 1)
  {
    setColor(behavior->color0, behavior->stringID, behavior->stringLen);
  }
  else
  {
    setColor(0, behavior->stringID, behavior->stringLen);
  }
  if (behavior->twinkleStep++ == 2*behavior->twinkleStepMax)
  {
    behavior->inProcess = 0;
    setColor(0, behavior->stringID, behavior->stringLen);
  }
}

void flame(struct led *behavior)
{
  int red, green, blue;
  rgbBreak(behavior->color0, &red, &green, &blue);
  if (red > 0)
  {
    red = (red/2) + (rand() % (red-(red/2)));
  }
  else
  {
    red = 0;
  }
  if (green > 0)
  {
    green = (green/2) + (rand() % (green-(green/2)));
  }
  else
  {
    green = 0;
  }
  if (blue > 0)
  {
    blue = (blue/2) + (rand() % (blue-(blue/2)));
  }
  else
  {
    blue = 0;
  }
  setColor(rgbMake(red, green, blue), behavior->stringID, behavior->stringLen);
}

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

