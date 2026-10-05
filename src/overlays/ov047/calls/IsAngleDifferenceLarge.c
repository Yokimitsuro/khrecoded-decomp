#include "nitro/types.h"

BOOL IsAngleDifferenceLarge(int from, int to)
{
    int diff = (u16)(to - from);

    if (diff <= 0x400 || 0x10000 - diff <= 0x400) {
        return FALSE;
    }
    return TRUE;
}
