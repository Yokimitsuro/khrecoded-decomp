#include "nitro/types.h"

#define REG_SQRTCNT (*(vu16 *)0x040002b0)
#define REG_SQRT_RESULT (*(vs32 *)0x040002b4)

s32 SqrtResultRounded(void)
{
    while (REG_SQRTCNT & 0x8000) {
    }
    return (REG_SQRT_RESULT + 1) >> 1;
}
