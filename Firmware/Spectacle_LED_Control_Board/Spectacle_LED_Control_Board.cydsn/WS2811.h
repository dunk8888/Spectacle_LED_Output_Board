/****************************************************************************
WS2811.h
Header file for WS2811 related constants
Mike Hord @ SparkFun Electronics
24 Jan 2017
https://github.com/sparkfun/Spectacle_LED_Output_Board

Defines a few constants for color shifting in WS2811 LEDs.

Development environment specifics:
Developed in PSoC Creator 4.0

This code is beerware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!
****************************************************************************/

#ifndef __ws2811_h__
#define __ws2811_h__

#define GREEN_SHIFT 16
#define BLUE_SHIFT  0
#define RED_SHIFT   8

#define GREEN_MASK  0x00FF0000
#define BLUE_MASK   0x000000FF
#define RED_MASK    0x0000FF00

#endif
