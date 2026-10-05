#include "nitro/types.h"

extern int data_02060388;
extern int ClampValueByMode(int value, int index);
extern void GXx_SetMasterBrightness_(volatile unsigned short *dst, int value);

void SetSecondaryBrightness(int value)
{
    int brightness = ClampValueByMode(value, 1);
    *((signed char *)&data_02060388 + 2) = brightness;
    volatile unsigned short *dispstat = (volatile unsigned short *)0x04000004;
    if (*dispstat & 1) {
        GXx_SetMasterBrightness_((volatile unsigned short *)0x0400106c, brightness);
        *(u8 *)&data_02060388 &= 0xfd;
        return;
    }
    *(u8 *)&data_02060388 |= 2;
}
