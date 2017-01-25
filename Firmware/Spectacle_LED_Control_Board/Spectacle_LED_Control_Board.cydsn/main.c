/****************************************************************************
main.c
Main code file for Spectacle LED output board project
Mike Hord @ SparkFun Electronics
24 Jan 2017
https://github.com/sparkfun/Spectacle_LED_Output_Board

This file includes main(), which configures the hardware for the system as
well as monitoring the data coming from the director board.

Development environment specifics:
Developed in PSoC Creator 4.0

This code is beerware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!
****************************************************************************/

#include <project.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "led.h"
#include "spectacle.h"
#include "programming.h"
#include "LED_effects.h"
#include "WS2811.h"

#define I2C_BUFFER_SIZE 256
#define I2C_BUFFER_RW_BOUNDARY 256

// systemTimer is incremented in the tickISR, which occurs once a millisecond.
//  It's the timebase for the entire firmware, upon which all other timing
//  is based.
volatile int32 systemTimer = 0;
CY_ISR_PROTO(tickISR);

// led is a struct which tracks the desired behavior of a single channel. A 
// single string of LEDs may have more than one channel associated with it,
// however, only one channel of behavior will be actively displayed at a time.
//struct led *behaviors;
struct led behaviors[10];
// behaviorListLen tracks the number of behaviors that have been uploaded from
// the director. We cycle through this number of behaviors on every go around
// of the 100Hz timer.
int behaviorListLen = 0;

// mailboxes is where our channel data comes in. A spectacle system can have
// up to 64 channels of behaviors, each of which is an int16.
int16 mailboxes[128];

// not everything that comes and goes via I2C is "mail", so we also create this
// general purpose pointer to access the I2C memory area when we don't want to
// create the impression that we're getting or sending mail.
volatile uint8 *I2C_Mem;

uint8 fading[3] = {0,0,0};
int32 fadeTimer[3] = {0,0,0};

int main()
{
  CyGlobalIntEnable; /* Enable global interrupts. */
  StripLights_Start(); 
  StripLights_Dim(0);
  StripLights_MemClear(0);
  StripLights_Trigger(1); 
  while( StripLights_Ready() == 0);
  StripLights_Trigger(1); 

  // We need to clear any cruft from the mailboxes to avoid spurious behavior.
  bzero(mailboxes, 128);

  // Point our GP I2C memory pointer at the I2C memory area.
  I2C_Mem = (uint8*)mailboxes;

  // Clear the programming setup bytes so we don't accidentally go into
  // programming mode when that becomes available.
  I2C_Mem[PROG_ENABLE_REG] = 0;
  I2C_Mem[PROG_READY_REG] = 0;
  I2C_Mem[DATA_READY_REG] = 0;
  I2C_Mem[BOARD_ID_REG] = BOARD_ID;

  // This is the startup code for the incoming I2C peripheral. We first enable
  // the peripheral, then tell it what it needs to know about the memory it
  // will be looking at for later decision making.
  EZI2C_Start();
  EZI2C_EzI2CSetBuffer1(I2C_BUFFER_SIZE, I2C_BUFFER_RW_BOUNDARY, (uint8*)mailboxes);
  
  // Start the UART. This is only a debugging tool.
  UART_Start();
  UART_UartPutString("Hello world");

  // ARM devices have an internal system tick which can be used as a timebase
  // without having to tie up additional system resources. Here we set it up to
  // point to our system tick ISR and configure it to occur once every 48000
  // clock ticks, which is once per millisecond on our 48MHz processor.
  CyIntSetSysVector((SysTick_IRQn + 16), tickISR);
  SysTick_Config(48000);
  
  // Variables used inside main().
  int32 _100HzTick = 0;
  int32 _2HzTick = 0;
  int32 _20HzTick = 0;
  int i = 0;
  
  // Assign memory to the "behaviors" array of structs.
//  behaviors = malloc(64*sizeof(struct led));

  // Turn the LED on. This is a good way to check that initialization has
  // passed; if the LED is on but not blinking the error is after init.
  LED_Write(1);

  for(;;)
  {
    // 100Hz service loop
    if ((systemTimer - 10) > _100HzTick)
    {
      _100HzTick = systemTimer;

      if (I2C_Mem[PROG_ENABLE_REG] == 1)
      {
        program();
        I2C_OUT_EN_Write(0);
      }
      if (I2C_Mem[CONFIGURED_REG] == 1)
      {
        EZI2C_EzI2CSetAddress1(I2C_Mem[I2C_ADDR_REG]);
        I2C_Mem[CONFIGURED_REG] = 0;
        I2C_OUT_EN_Write(1);
      }
      // Behavior loop. We'll cycle through this loop for each behavior that we
      // received from the director board, checking that behavior's mailbox to
      // see if any data has been received for that channel. We'll then do
      // something based on that behavior.
      for (i = 0; i < behaviorListLen; i++)
      {
        switch(behaviors[i].mode)
        {
          case SET_COLOR:
            if (behaviors[i].inProcess == 1)
            {
              if (behaviors[i].ledTimer + behaviors[i].delay < systemTimer)
              {
                behaviors[i].inProcess = 0;
                setColor(behaviors[i].color0, behaviors[i].stringID, 
                         behaviors[i].stringLen);
              }
            }
            else 
            {
              if (mailboxes[behaviors[i].channel] > behaviors[i].threshold)
              {
                behaviors[i].ledTimer = systemTimer;
                behaviors[i].inProcess = 1;
              }
            }
            break;
          case SET_PIXEL:
            if (mailboxes[behaviors[i].channel] > behaviors[i].threshold)
            {
              setColor(0, behaviors[i].stringID, behaviors[i].stringLen);
              StripLights_Pixel(behaviors[i].pixel, behaviors[i].stringID, 
                                behaviors[i].color0);
            }
            break;
          case FADE_STRING:
            if (fading[behaviors[i].stringID] == 0)
            {
              fadeTimer[behaviors[i].stringID] = systemTimer;
              if (mailboxes[behaviors[i].channel] > behaviors[i].threshold)
              {
                fadeString(&behaviors[i]);
              }
              else
              {
                setColor(0, behaviors[i].stringID, behaviors[i].stringLen);
              }
            }
            else
            {
              if (mailboxes[behaviors[i].channel] > behaviors[i].threshold)
              {
                if (fadeTimer[behaviors[i].stringID] + behaviors[i].delay < systemTimer)
                {
                  fadeTimer[behaviors[i].stringID] = systemTimer;
                  fadeString(&behaviors[i]);
                }
              }
              else
              {
                fading[behaviors[i].stringID] = 0;
              }
            }
            break;
          case PARTIAL_FILL:
            if (behaviors[i].inProcess == 1)
            {
              if (behaviors[i].ledTimer + behaviors[i].delay < systemTimer)
              {
                behaviors[i].inProcess = 0;
                setColor(0, behaviors[i].stringID, behaviors[i].stringLen);
                setColor(behaviors[i].color0, behaviors[i].stringID, 
                         behaviors[i].pixel);
              }
            }
            else 
            {
              if (mailboxes[behaviors[i].channel] > behaviors[i].threshold)
              {
                behaviors[i].ledTimer = systemTimer;
                behaviors[i].inProcess = 1;
              }
            }
            break;
          case RAINBOW:
            if (mailboxes[behaviors[i].channel] > behaviors[i].threshold)
            {
              if (behaviors[i].ledTimer + behaviors[i].delay < systemTimer)
              {
                behaviors[i].ledTimer = systemTimer;
                rainbow(&behaviors[i]);
              }
            }
            else
            {
              setColor(0, behaviors[i].stringID, behaviors[i].stringLen);
            }
            break;
          case THEATER_CHASE:
            if (mailboxes[behaviors[i].channel] > behaviors[i].threshold)
            {
              if (behaviors[i].ledTimer + behaviors[i].delay < systemTimer)
              {
                behaviors[i].ledTimer = systemTimer;
                theaterchase(&behaviors[i]);
              }
            }
            else
            {
              setColor(0, behaviors[i].stringID, behaviors[i].stringLen);
            }
            break;
          case SCAN:
            if (mailboxes[behaviors[i].channel] > behaviors[i].threshold)
            {
              if (behaviors[i].ledTimer + behaviors[i].delay < systemTimer)
              {
                behaviors[i].ledTimer = systemTimer;
                scan(&behaviors[i]);
              }
            }
            else
            {
              setColor(0, behaviors[i].stringID, behaviors[i].stringLen);
            }
            break;
          case TWINKLE:
            if (mailboxes[behaviors[i].channel] > behaviors[i].threshold)
            {
              if (behaviors[i].inProcess == 1)
              {
                if (behaviors[i].stepCntr++ == behaviors[i].stepDelay)
                {
                  behaviors[i].stepCntr = 0;
                  twinkle(&behaviors[i]);
                }
              }
              else if (behaviors[i].ledTimer + behaviors[i].delay < systemTimer)
              {
                behaviors[i].ledTimer = systemTimer;
                if (rand() % behaviors[i].pixel == 1)
                {
                  behaviors[i].stepDelay = (rand()%3) + 3;
                  behaviors[i].stepCntr = 0;
                  twinkle(&behaviors[i]);
                }
              }
            }
            else
            {
              setColor(0, behaviors[i].stringID, behaviors[i].stringLen);
            }
            break;
          case LIGHTNING:
            if (mailboxes[behaviors[i].channel] > behaviors[i].threshold)
            {
              if (behaviors[i].inProcess == 1)
              {
                lightning(&behaviors[i]);
              }
              else if (behaviors[i].ledTimer + behaviors[i].delay < systemTimer)
              {
                behaviors[i].ledTimer = systemTimer;
                if (rand() % behaviors[i].pixel == 1)
                {
                  lightning(&behaviors[i]);
                }
              }
            }
            else
            {
              setColor(0, behaviors[i].stringID, behaviors[i].stringLen);
            }
            break;
          case FLAME:
            if (mailboxes[behaviors[i].channel] > behaviors[i].threshold)
            {
              if (behaviors[i].inProcess == 1)
              {
                if (behaviors[i].stepCntr++ == behaviors[i].stepDelay)
                {
                  behaviors[i].stepCntr = 0;
                  flame(&behaviors[i]);
                }
              }
              else if (behaviors[i].inProcess == 0)
              {
                behaviors[i].inProcess = 1;
                behaviors[i].stepCntr = 0;
                behaviors[i].stepDelay = 5;
              }
            }
            else
            {
              setColor(0, behaviors[i].stringID, behaviors[i].stringLen);
              behaviors[i].inProcess = 0;
            }
            break;
        }
      }

      StripLights_Trigger(1); 
    } // End 100Hz service loop

    // 20Hz service loop
    if ((systemTimer - 50) > _20HzTick)
    {
      _20HzTick = systemTimer;
    }

    // 2Hz service loop
    if ((systemTimer - 500) > _2HzTick)
    {
      _2HzTick = systemTimer;
      if (LED_Read() != 0)
      {
        LED_Write(0);
      }
      else
      {
        LED_Write(1);
      }
    }
  }
}

CY_ISR(tickISR)
{
  systemTimer++;
}

/* [] END OF FILE */

