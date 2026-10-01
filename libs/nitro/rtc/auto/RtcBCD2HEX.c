#include "libs/nitro/rtc/rtc_internal.h"

u32 RtcBCD2HEX(u32 bcd)
{
    u32 hex = 0;
    s32 i;
    s32 weight;

    for (i = 0; i < 8; i++) {
        if (((bcd >> (i * 4)) & 0x0f) >= 10) {
            return hex;
        }
    }

    for (i = 0, weight = 1; i < 8; i++, weight *= 10) {
        hex += (((bcd >> (i * 4)) & 0x0f) * weight);
    }

    return hex;
}
