#include "nitro/types.h"

/* Adds with overflow check */
BOOL TryAddInt32A(s32 *value, s32 addend)
{
    s32 current = *value;

    if (addend < 0) {
        if (current < 0) {
            s32 limit = (s32)0x80000000 - current;
            if (addend < limit) {
                return FALSE;
            }
        }
    } else {
        if (current > 0) {
            s32 limit = 0x7fffffff - current;
            if (addend > limit) {
                return FALSE;
            }
        }
    }

    *value = current + addend;
    return TRUE;
}
