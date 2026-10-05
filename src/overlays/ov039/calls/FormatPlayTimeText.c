#include "nitro/types.h"

extern void *OS_SNPrintf_0202e094(char *dst, unsigned int len, const char *fmt, ...);
extern const char data_ov039_020be9e4[];

u32 FormatPlayTimeText(char *buffer, u32 seconds)
{
    if (seconds > 3599999) {
        seconds = 3599999;
    }
    OS_SNPrintf_0202e094(buffer, 10, data_ov039_020be9e4, seconds / 3600, seconds / 60 % 60, seconds % 60);
    return seconds;
}
