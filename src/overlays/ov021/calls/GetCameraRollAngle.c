#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

extern u8 NNS_G3dGlb_cameraMtx[];
extern void func_01ff913c(const void *src, MtxFx33 *dst);
extern VecFx32 GetUnitRejectionFromAxis(const VecFx32 *v, const VecFx32 *normal);
extern s16 AngleBetweenVecs(const VecFx32 *a, const VecFx32 *b);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

u16 GetCameraRollAngle(void)
{
    u16 angle;
    MtxFx33 camera;
    VecFx32 projected;
    VecFx32 result;
    VecFx32 upCopy;
    MtxFx33 fetched;
    VecFx32 up;

    func_01ff913c(NNS_G3dGlb_cameraMtx, &fetched);
    camera = fetched;
    up.x = 0;
    up.y = FX32_ONE;
    up.z = 0;
    upCopy = up;
    result = GetUnitRejectionFromAxis(&upCopy, (VecFx32 *)&camera._20);
    projected = result;
    angle = AngleBetweenVecs(&projected, (VecFx32 *)&camera._10);
    if (angle <= 400) {
        angle = 0;
    } else if (VEC_DotProduct(&projected, (VecFx32 *)&camera._00) < 0) {
        angle = -(s16)angle;
    }
    return angle;
}
