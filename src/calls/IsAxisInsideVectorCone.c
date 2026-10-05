#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void func_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

static inline VecFx32 Cross(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 cross;
    func_01ff9ea8(a, b, &cross);
    return cross;
}

static inline s32 Sign(fx32 value)
{
    return value >= 0 ? 1 : -1;
}

BOOL IsAxisInsideVectorCone(const VecFx32 *vecA, const VecFx32 *vecB, const VecFx32 *vecC, const VecFx32 *axis)
{
    const VecFx32 *vecs[3];
    VecFx32 separator;
    fx32 prevDot;
    int i;

    vecs[0] = vecA;
    vecs[1] = vecB;
    vecs[2] = vecC;
    for (i = 0; i < 3; i++) {
        separator = Cross(vecs[i], axis);
        fx32 nextDot = VEC_DotProduct(&separator, vecs[(i + 1) % 3]);
        prevDot = VEC_DotProduct(&separator, vecs[(i + 2) % 3]);
        if (Sign(nextDot) == Sign(prevDot) || nextDot == 0 || prevDot == 0) {
            return FALSE;
        }
    }
    return TRUE;
}
