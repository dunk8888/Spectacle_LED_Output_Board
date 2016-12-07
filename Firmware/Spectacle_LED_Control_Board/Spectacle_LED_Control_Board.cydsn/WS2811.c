#include <project.h>
#include <stdbool.h>
#include "WS2811.h"

uint32 buffer[3][60];
extern int stringLen[3];

void updateString(uint8 stringID)
{
  int i = 0;
  for (i = 0; i< stringLen[stringID]; i++)
  {
  CyGlobalIntDisable;
    pixelOut(buffer[stringID][i], stringID);
  CyGlobalIntEnable;
  }
}

inline void pixelOut(uint32 pixelVal, uint8 stringID)
{
  int i = 0;
  uint32 mask = 0x00800000;
  /*
  int red = (pixelVal>>RED_SHIFT)&0x000000FF;
  int blue = (pixelVal>>BLUE_SHIFT)&0x000000FF;
  int green = (pixelVal>>GREEN_SHIFT)&0x000000FF;

  red *= (brightnessMask/255)&0x000000FF;
  blue *= (brightnessMask/255)&0x000000FF;
  green *= (brightnessMask/255)&0x000000FF;

  pixelVal = red<<RED_SHIFT | blue<<BLUE_SHIFT | green<<GREEN_SHIFT;
  */
 
  uint8 portMask = 0x01;
  uint32 address = CYREG_GPIO_PRT3_DR;
  if (stringID == 0)
  {
    portMask = 0x01;
    address = CYREG_GPIO_PRT3_DR;
  }
  else if (stringID == 1)
  {
    portMask = 0x40;
    address = CYREG_GPIO_PRT2_DR;
  }
  else
  {
    portMask = 0x01;
    address = CYREG_GPIO_PRT1_DR;
  }
  
  for (i = 0; i<24; i++)
  {
    if (!(mask & pixelVal)) 
    {
      zero(address, portMask);
    }
    else                 one(address, portMask);
    mask = mask>>1;
  }
}

inline void zero(uint32 address, uint8 mask)
// T0H = 350ns +/- 150ns
// T0L = 1360ns +/- 150ns
{
  
  * (reg32 *)address |= mask;
  /*__asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");*/
  __asm("nop");
  __asm("nop");
  * (reg32 *)address &= ~mask;
  /*__asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");*/
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
}

inline void one(uint32 address, uint8 mask)
// T1H = 1360ns +/- 150ns
// T1L = 350ns +/- 150ns
{
  * (reg32 *)address |= mask;
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  * (reg32 *)address &= ~mask;
  /*__asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");
  __asm("nop");*/
}
