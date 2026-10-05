#include "nitro/types.h"

extern u32 func_ov001_02068e80(void);
extern u32 _u32_div_f(u32 numerator, u32 denominator);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);

void SaveElapsedSeconds(void)
{
    int seconds = _u32_div_f(func_ov001_02068e80(), 1000);

    if (seconds >= 0x20000) {
        seconds = 0x1ffff;
    }
    WriteSessionPackedBits(0x35d2, 0x11, seconds);
}
