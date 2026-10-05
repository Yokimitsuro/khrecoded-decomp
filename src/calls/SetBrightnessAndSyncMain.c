#include "nitro/types.h"

extern int data_02060388;
extern int ClampValueByMode(int value, int index);
extern void GXx_SetMasterBrightness_(volatile unsigned short *dst, int value);

void SetBrightnessAndSyncMain(int value)
{
    int brightness = ClampValueByMode(value, 0);
    *((signed char *)&data_02060388 + 1) = brightness;
    volatile unsigned short *dispstat = (volatile unsigned short *)0x04000004;
    if (*dispstat & 1) {
        GXx_SetMasterBrightness_(dispstat + 0x34, brightness);
        *(u8 *)&data_02060388 &= 0xfe;
        return;
    }
    *(u8 *)&data_02060388 |= 1;
}
