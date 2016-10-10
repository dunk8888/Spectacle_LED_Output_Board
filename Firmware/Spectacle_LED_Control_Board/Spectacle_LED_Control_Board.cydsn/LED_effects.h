#ifndef __led_effects_h__
#define __led_effects_h__

#include <stdbool.h>

void setColor(uint32 color, uint8 stringID);
void setPixel(uint32 color, uint8 pixel, uint8 stringID);
void fadeString(uint32 color0, uint32 color1, uint8 stringID);
void partialFill(uint32 color, uint8 pixel, uint8 stringID);
void rainbow(int iteration, uint8 stringID);
void theaterchase(uint32 color, uint8 stringID);
void scan(uint32 color, uint8 stringID);
bool twinkle(uint32 color, uint8 stringID);
bool lightning(uint32 color, uint8 stringID);

enum {SET_COLOR, SET_PIXEL, FADE_STRING, PARTIAL_FILL, RAINBOW,
      THEATER_CHASE, SCAN, TWINKLE, LIGHTNING};

uint32 wheel(uint8 wheelPos);
uint32 rgbMake(int red, int green, int blue);
void rgbBreak(uint32 color, int *red, int *green, int *blue);

#endif

