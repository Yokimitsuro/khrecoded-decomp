#include "nitro/types.h"
#include "nitro/fx_types.h"

extern VecFx32 *func_ov001_0206dc4c(int index);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 FX_Mul(fx32 left, fx32 right);

BOOL CheckSideOffsetInRange(const VecFx32 *position, const VecFx32 *facing, fx32 low, fx32 high, s32 direction, fx32 *outOffset)
{
    BOOL inside = FALSE;
    VecFx32 delta;
    fx32 offset;

    VEC_Subtract(position, func_ov001_0206dc4c(0), &delta);
    offset = FX_Mul(delta.x, facing->z) - FX_Mul(delta.z, facing->x);
    if (direction == 0x200) {
        if (offset > low && offset < high) {
            inside = TRUE;
        }
    } else {
        if (offset < low && offset > high) {
            inside = TRUE;
        }
    }
    if (inside) {
        *outOffset = offset;
    }
    return inside;
}
