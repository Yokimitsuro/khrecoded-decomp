#include "nitro/types.h"
#include "nitro/fx.h"

extern s16 data_02053580[];
extern u16 GetLinkedAngleOffset(int entity);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void AdvanceModelAnimation(void *model, fx32 step, VecFx32 *out);
extern int FX_Div(int numer, int denom);
extern void func_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern void MTX_MultVec33(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);

void ComputeRootMotionDelta(int entity, VecFx32 *out)
{
    MtxFx33 rotation;
    VecFx32 motion;
    int index = GetLinkedAngleOffset(entity) >> 4;
    int scale;
    MTX_RotY33_(&rotation, -data_02053580[index], -data_02053580[(0x400 - index) & 0xfff]);
    AdvanceModelAnimation((void *)(entity + 0x874), *(fx32 *)(entity + 0x9ec), &motion);
    scale = FX_Div(0x1000, *(int *)(entity + 0x340));
    if (scale != 0x1000) {
        fx32 height = motion.y;
        func_01ffafb4(scale, &motion, &motion);
        motion.y = height;
    }
    MTX_MultVec33(&motion, &rotation, out);
}
