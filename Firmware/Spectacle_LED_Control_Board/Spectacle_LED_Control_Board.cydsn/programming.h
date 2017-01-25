/****************************************************************************
programming.h
Header for programming.c
Mike Hord @ SparkFun Electronics
24 Jan 2017
https://github.com/sparkfun/Spectacle_LED_Output_Board

Defines I2C addresses for programming.

Development environment specifics:
Developed in PSoC Creator 4.0

This code is beerware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!
****************************************************************************/

#ifndef __programming_h__
#define __programming_h__

#include <project.h>
#include "led.h"

#define PROG_ENABLE_REG 200
#define PROG_READY_REG  201
#define DATA_READY_REG  202
#define INC_STRUCT_TOP  128

void program(void);

#endif

