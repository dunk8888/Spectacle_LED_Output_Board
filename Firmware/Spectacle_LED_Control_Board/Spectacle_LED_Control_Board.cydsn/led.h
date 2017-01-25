/****************************************************************************
led.h
Main code file for Spectacle LED output board project
Mike Hord @ SparkFun Electronics
24 Jan 2017
https://github.com/sparkfun/Spectacle_LED_Output_Board

Defines the behavioral structure of the LED output board. This is uploaded
to the board by the director board.

Development environment specifics:
Developed in PSoC Creator 4.0

This code is beerware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!
****************************************************************************/

#ifndef __audio_h__
#define __audio_h__
#include "project.h"
    
#define USER_DATA_LEN 19
    
#pragma pack(1)
struct led
{
  uint8 channel;
  int16 threshold;
  uint8 mode;
  uint8 stringID;
  uint32 color0;
  uint32 color1;
  uint8 pixel;
  uint8 stringLen;
  int32 delay;
    // end of user definable attributes
  int8 stepDelayMax;
  int8 stepDelay;
  int8 stepCntr;
  int32 ledTimer;
  int32 iteration;
  uint8 fading;
  uint8 inProcess;
  int8 direction;
  int8 redStep;
  int8 greenStep;
  int8 blueStep;
  int16 red;
  int16 green;
  int16 blue;
  int8 twinkleStepMax;
  int8 twinkleStep;

};
#pragma pack()

#endif

