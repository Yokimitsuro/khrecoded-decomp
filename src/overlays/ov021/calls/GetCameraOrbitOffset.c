#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

extern u8 NNS_G3dGlb_cameraMtx[];
extern s16 data_02053580[];
extern void func_01ff913c(const void *src, MtxFx33 *dst);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

VecFx32 GetCameraOrbitOffset(fx32 radians)
{
    MtxFx33 camera;
    VecFx32 offset;
    MtxFx33 fetched;
    VecFx32 axis;
    VecFx32 sum;
    VecFx32 result;
    int index;

    func_01ff913c(NNS_G3dGlb_cameraMtx, &fetched);
    camera = fetched;
    index = (int)((((s64)radians << 16) / 0x6488) & 0xffff) >> 4;
    axis = *(VecFx32 *)&camera._00;
    ScaleVecFx32InPlace(&axis, data_02053580[(0x400 - index) & 0xfff]);
    offset = axis;
    VEC_MultAdd(data_02053580[index], (VecFx32 *)&camera._10, &offset, &sum);
    result = sum;
    offset = result;
    return result;
}
