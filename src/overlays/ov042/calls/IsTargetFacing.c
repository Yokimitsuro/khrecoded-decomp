#include "nitro/types.h"

extern int VEC_DotProduct(const void *a, const void *b);

BOOL IsTargetFacing(u8 *self, int unused, u8 *target) {
    if (target != NULL && VEC_DotProduct(target + 4, *(u8 **)(self + 0x24) + 0xc4) <= 0) {
        return FALSE;
    }
    return TRUE;
}
