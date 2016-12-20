#ifndef __led_effects_h__
#define __led_effects_h__
    
#include "project.h"
#include "led.h"

void setColor(uint32 color, uint8 stringID, uint8 pixel);
void setPixel(struct led *behavior);
void fadeString(struct led *behavior);
void partialFill(struct led *behavior);
void rainbow(struct led *behavior);
void theaterchase(struct led *behavior);
void scan(struct led *behavior);
void twinkle(struct led *behavior);
void lightning(struct led *behavior);
void flame(struct led *behavior);

enum {SET_COLOR, SET_PIXEL, FADE_STRING, PARTIAL_FILL, RAINBOW,
      THEATER_CHASE, SCAN, TWINKLE, LIGHTNING, FLAME};

uint32 wheel(uint8 wheelPos);
uint32 rgbMake(int red, int green, int blue);
void rgbBreak(uint32 color, int *red, int *green, int *blue);

#endif

