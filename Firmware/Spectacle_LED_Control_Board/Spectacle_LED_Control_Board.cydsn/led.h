#ifndef __audio_h__
#define __audio_h__
#include "project.h"
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
  uint8 twinkleStepMax;
  uint8 twinkleStep;

};
#pragma pack()

#endif

