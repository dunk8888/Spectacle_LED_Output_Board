#include <project.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "LED_effects.h"
#include "WS2811.h"

#define I2C_BUFFER_SIZE 16
#define I2C_BUFFER_RW_BOUNDARY 16

volatile int32 systemTimer = 0;

extern bool fading;

int stringLen[3] = {30,10,20};

CY_ISR_PROTO(tickISR);

int brightnessMask;

int main()
{
  CyGlobalIntEnable; /* Enable global interrupts. */
  
  uint8 registerSpace[I2C_BUFFER_SIZE];

  uint8 *r_change;
  uint8 *r_mode0;
  uint8 *r_active0;
  uint8 *r_red0;
  uint8 *r_green0;
  uint8 *r_blue0;
  uint8 *r_random;
  uint32 *r_delay0;
  uint32 tick0=0;
  bool midFunction0 = false;
  uint8 iteration0 = 0;

  r_change = &registerSpace[0];

  r_mode0 = &registerSpace[1];
  r_active0 = &registerSpace[2];
  r_red0 = &registerSpace[3];
  r_green0 = &registerSpace[4];
  r_blue0 = &registerSpace[5];
  r_random = &registerSpace[6];
  r_delay0 = (uint32*)&registerSpace[7];
  *r_delay0 = 200;
  *r_random = 5;
  *r_mode0 = SET_COLOR;
  *r_active0 = 0;
  *r_red0 = 0xff;
  *r_green0 = 0xff;
  *r_blue0 = 0xff;

  EZI2C_Start();
  EZI2C_EzI2CSetBuffer1(I2C_BUFFER_SIZE, I2C_BUFFER_RW_BOUNDARY, registerSpace);
  
  UART_Start();
  
  CyIntSetSysVector((SysTick_IRQn + 16), tickISR);
  SysTick_Config(48000);
  
  int32 _100HzTick = 0;
  int32 _2HzTick = 0;
  int32 _20HzTick = 0;
  uint32 rxBuffer = 0;
  int i = 0;
  
  UART_UartPutString("Hello world");
  LED_Write(1);
  
  for(;;)
  {
    // 100Hz service loop
    if ((systemTimer - 10) > _100HzTick)
    {
      _100HzTick = systemTimer;

      // Serial RX handler
      rxBuffer = UART_UartGetChar();
      if (rxBuffer == 'r')
      {
        for (i=0; i < I2C_BUFFER_SIZE; i++)
        {
          UART_UartPutChar(registerSpace[i]);
        }
      } // End serial RXhandler

    } // End 100Hz service loop

    // 20Hz service loop
    if ((systemTimer - 50) > _20HzTick)
    {
      _20HzTick = systemTimer;
      updateString(0);
      updateString(1);
      updateString(2);
      brightnessMask = 255*30/(stringLen[0]+stringLen[1]+stringLen[2]);
      if (brightnessMask > 255)
      {
        brightnessMask = 255;
      }
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

    // NHz service loop, for LED effects
    if ((systemTimer - *r_delay0) > tick0)
    {
      tick0 = systemTimer;
      if (*r_active0 == 1)
      {  
        // TWINKLE mode handler
        if (*r_mode0 == TWINKLE)
        {
          if (midFunction0 == false)
          {
            if ((rand() % (*r_random)) == 1)
            {
              midFunction0 = true;
            }
          }
          if (midFunction0 == true)
          {
            uint32 colorTemp = rgbMake(*r_red0, *r_green0, *r_blue0);
            midFunction0 = twinkle(colorTemp, 0);
          }
        } // END TWINKKLE mode handler

        // LIGHTNING mode handler
        if (*r_mode0 == LIGHTNING)
        {
          if (midFunction0 == false)
          {
            if ((rand() % (*r_random)) == 0)
            {
              midFunction0 = true;
            }
          }
          if (midFunction0 == true)
          {
            uint32 colorTemp = rgbMake(*r_red0, *r_green0, *r_blue0);
            midFunction0 = lightning(colorTemp, 0);
          }
        } // END LIGHTNING mode handler

        // SCAN mode handler
        if (*r_mode0 == SCAN)
        {
          scan(rgbMake(*r_red0, *r_green0, *r_blue0), 0);
        } // END SCAN mode handler

        // THEATER_CHASE mode handler
        if (*r_mode0 == THEATER_CHASE)
        {
          theaterchase(rgbMake(*r_red0, *r_green0, *r_blue0), 0);
        } // END THEATER_CHASE mode handler

        // RAINBOW mode handler
        if (*r_mode0 == RAINBOW)
        {
          rainbow(iteration0++, 0);
        } // END RAINBOW mode handler

        // FADE_STRING mode handler
        if (*r_mode0 == FADE_STRING)
        {
          fadeString(0,rgbMake(*r_red0, *r_green0, *r_blue0), 0);
        } // END FADE_STRING mode handler

        // PARTIAL_FILL mode handler
        if (*r_mode0 == PARTIAL_FILL)
        {
          partialFill(rgbMake(*r_red0, *r_green0, *r_blue0), *r_random, 0);
        } // END PARTIAL_FILL mode handler

        // SET_PIXEL mode handler
        if (*r_mode0 == SET_PIXEL)
        {
          setPixel(rgbMake(*r_red0, *r_green0, *r_blue0), *r_random, 0);
        } // END SET_PIXEL mode handler

        // SET_COLOR mode handler
        if (*r_mode0 == SET_COLOR)
        {
          setColor(rgbMake(*r_red0, *r_green0, *r_blue0), 0);
        }
      }
    }
  }
}

CY_ISR(tickISR)
{
  systemTimer++;
}



/* [] END OF FILE */

