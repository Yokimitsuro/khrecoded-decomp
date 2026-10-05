#include "nitro/types.h"

extern void OS_GetMacAddress(u8 *macAddress);
extern unsigned long long _s32_div_f(u32 numerator, u32 denominator);
extern u32 gVBlankCount;

u16 GetDispersionScanPeriod(void)
{
    u8 mac[6];
    u16 sum;
    int i;
    u32 remainder;

    OS_GetMacAddress(mac);

    i = 0;
    sum = 0;
    do {
        u8 byte = mac[i];
        i++;
        sum = sum + byte;
    } while (i < 6);

    sum = sum + (u16)gVBlankCount;
    remainder = (u32)(_s32_div_f((u16)(sum * 13), 10) >> 32);

    return (u16)(remainder + 30);
}
