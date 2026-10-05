#include "nitro/types.h"
#include "nitro/fx_types.h"

extern VecFx32 *func_ov001_0206dc4c(int index);
extern VecFx32 *func_ov021_020af5d4(void);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 FX_Mul(fx32 left, fx32 right);
extern BOOL ScanActorsForSideTarget(const VecFx32 *facing, fx32 low, fx32 high, s32 direction, fx32 *outOffset);
extern BOOL ScanObjectsForSideTarget(const VecFx32 *facing, fx32 low, fx32 high, s32 direction, fx32 *outOffset);
extern BOOL ScanRecordSlotsForSideTarget(const VecFx32 *facing, fx32 low, fx32 high, s32 direction, fx32 *outOffset);

BOOL FindSideTarget(s32 direction, const VecFx32 *position, fx32 *limit)
{
    BOOL found = FALSE;
    VecFx32 *playerPos;
    fx32 bound;
    fx32 offset;
    fx32 nextOffset;
    VecFx32 facing;
    VecFx32 delta;

    playerPos = func_ov001_0206dc4c(0);
    VEC_Subtract(playerPos, func_ov021_020af5d4(), &facing);
    VEC_Subtract(position, playerPos, &delta);
    offset = FX_Mul(delta.x, facing.z) - FX_Mul(delta.z, facing.x);
    if (limit == NULL) {
        if (direction == 0x200) {
            bound = 0x7fffffff;
        } else {
            bound = 0x80000000;
        }
    } else {
        bound = *limit;
    }
    if (ScanActorsForSideTarget(&facing, offset, bound, direction, &nextOffset)) {
        bound = nextOffset;
        found = TRUE;
    }
    if (ScanObjectsForSideTarget(&facing, offset, bound, direction, &nextOffset)) {
        bound = nextOffset;
        found = TRUE;
    }
    if (ScanRecordSlotsForSideTarget(&facing, offset, bound, direction, &nextOffset)) {
        bound = nextOffset;
        found = TRUE;
    }
    if (limit != NULL) {
        *limit = bound;
    }
    return found;
}
