#include "nitro/types.h"
#include "nitro/fx_types.h"

extern const VecFx32 data_0205344c;
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern BOOL AreVecsWithinRange16(const VecFx32 *a, const VecFx32 *b);

static inline BOOL IsNearZero(const VecFx32 *vec, VecFx32 *scratch)
{
    *scratch = *vec;
    return AreVecsWithinRange16(scratch, &data_0205344c);
}

BOOL IsCrossNearZero(const VecFx32 *vec, const VecFx32 *axis, VecFx32 *out, BOOL verticalOnly)
{
    VecFx32 check;
    VecFx32 copy;
    VecFx32 cross;

    if (verticalOnly == 0) {
        VEC_CrossProduct(vec, axis, &cross);
    } else {
        cross.x = -(fx32)(((fx64)vec->z * axis->y + 0x800) >> 12);
        cross.y = 0;
        cross.z = (fx32)(((fx64)vec->x * axis->y + 0x800) >> 12);
    }
    copy = cross;
    if (!IsNearZero(&cross, &check)) {
        *out = copy;
        return FALSE;
    }
    return TRUE;
}


