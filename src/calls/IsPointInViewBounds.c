#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

extern MtxFx43 NNS_G3dGlb_cameraMtx;
extern const VecFx32 *func_ov042_020bd2b0(void);
extern const fx32 *func_ov042_020bd5b0(void);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void func_01ff913c(const MtxFx43 *src, MtxFx33 *dst);

static inline VecFx32 SubtractVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 out;
    VEC_Subtract(a, b, &out);
    return out;
}

static inline MtxFx33 GetViewRotation(void)
{
    MtxFx33 rotation;
    func_01ff913c(&NNS_G3dGlb_cameraMtx, &rotation);
    return rotation;
}

BOOL IsPointInViewBounds(const VecFx32 *point, fx32 margin)
{
    VecFx32 delta;
    MtxFx33 rotation;
    const fx32 *extent;
    fx32 distance;

    delta = SubtractVec(point, func_ov042_020bd2b0());
    rotation = GetViewRotation();
    extent = func_ov042_020bd5b0();
    distance = VEC_DotProduct((const VecFx32 *)rotation.m[0], &delta);
    if (distance < 0)
        distance = -distance;
    if (distance > extent[1] + margin)
        return FALSE;
    distance = VEC_DotProduct((const VecFx32 *)rotation.m[1], &delta);
    if (distance < 0)
        distance = -distance;
    if (distance > extent[2] + margin)
        return FALSE;
    return TRUE;
}
