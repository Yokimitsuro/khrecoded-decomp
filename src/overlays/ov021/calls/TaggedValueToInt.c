#include "nitro/types.h"

s32 TaggedValueToInt(s16 *tagged)
{
    s32 result = 0;
    if (*tagged == 0x10) {
        result = *(s32 *)(tagged + 2) >> 0xc;
    } else if (*tagged == 1) {
        result = *(s32 *)(tagged + 2);
    }
    return result;
}
