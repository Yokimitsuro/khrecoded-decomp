#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

extern const s16 data_02053580[];
extern int func_ov052_020ceb9c(int entity);
extern VecFx32 *func_ov052_020ceb74(int entity);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void func_01ff9404(const VecFx32 *vec, const MtxFx33 *mtx, VecFx32 *dst);
extern void func_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void func_ov046_020c1400(VecFx32 *pos, int kind, int arg);

void SpawnEffectAboveEntity(int entity, int arg)
{
    MtxFx33 rotation;
    VecFx32 offset;
    int cosAngle = func_ov052_020ceb9c(entity);
    int sinAngle = func_ov052_020ceb9c(entity);

    MTX_RotY33_(&rotation, data_02053580[sinAngle >> 4], data_02053580[(0x400 - (cosAngle >> 4)) & 0xfff]);
    offset.x = 0;
    offset.y = 0;
    offset.z = FX32_ONE * 4;
    func_01ff9404(&offset, &rotation, &offset);
    func_01ff9e0c(func_ov052_020ceb74(entity), &offset, &offset);
    offset.y += FX32_ONE * 4;
    func_ov046_020c1400(&offset, 3, arg);
}
