#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

extern const s16 data_02053580[];
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33(const VecFx32 *vec, const MtxFx33 *mtx, VecFx32 *dst);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);

void RotateOffsetAroundY(VecFx32 *out, const VecFx32 *origin, int angle, const VecFx32 *offset)
{
    VecFx32 point = *offset;
    MtxFx33 rotation;
    int index = angle >> 4;

    MTX_RotY33_(&rotation, data_02053580[index], data_02053580[(0x400 - index) & 0xfff]);
    MTX_MultVec33(&point, &rotation, &point);
    VEC_Add(&point, origin, &point);
    *out = point;
}

