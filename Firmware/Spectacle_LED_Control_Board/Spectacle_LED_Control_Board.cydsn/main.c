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

int stringLen[3] = {60,60,60};
int main()
{
  CyGlobalIntEnable; /* Enable global interrupts. */
  
  // We need to clear any cruft from the mailboxes to avoid spurious behavior.
  bzero(mailboxes, 128);

  // Point our GP I2C memory pointer at the I2C memory area.
  I2C_Mem = (uint8*)mailboxes;

  // Clear the programming setup bytes so we don't accidentally go into
  // programming mode when that becomes available.
  I2C_Mem[PROG_ENABLE_REG] = 0;
  I2C_Mem[PROG_READY_REG] = 0;
  I2C_Mem[DATA_READY_REG] = 0;

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
            if (mailboxes[behaviors[i].channel] > behaviors[i].threshold)
            {
             //stringLen[behaviors[i].stringID] = behaviors[i].stringLen;
              setColor(&behaviors[i]);
            }
            break;
          case SET_PIXEL:
            if (mailboxes[behaviors[i].channel] > behaviors[i].threshold)
            {
              setPixel(&behaviors[i]);
            }
            break;
          case FADE_STRING:
            break;
          case PARTIAL_FILL:
            break;
          case RAINBOW:
            break;
          case THEATER_CHASE:
            break;
          case SCAN:
            break;
          case TWINKLE:
            break;
          case LIGHTNING:
            break;
        }
      }

    } // End 100Hz service loop

    // 20Hz service loop
    if ((systemTimer - 50) > _20HzTick)
    {
      _20HzTick = systemTimer;
      updateString(0);
      updateString(1);
      updateString(2);
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

