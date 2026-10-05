#include "nitro/types.h"

BOOL IsWithinDelta16(s32 a, s32 b)
{
    if ((a - b < 0x10) && (-0x10 < a - b)) {
        return TRUE;
    }
    return FALSE;
}
