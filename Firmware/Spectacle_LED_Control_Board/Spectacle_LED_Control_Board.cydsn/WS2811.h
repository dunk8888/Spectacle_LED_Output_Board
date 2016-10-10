#ifndef __ws2811_h__
#define __ws2811_h__

#define GREEN_SHIFT 16
#define BLUE_SHIFT  0
#define RED_SHIFT   8

#define GREEN_MASK  0x00FF0000
#define BLUE_MASK   0x000000FF
#define RED_MASK    0x0000FF00

inline void one(uint32 address, uint8 mask);
inline void zero(uint32 address, uint8 mask);
inline void pixelOut(uint32 pixelVal, uint8 stringID);
void updateString(uint8 stringID);

#endif
