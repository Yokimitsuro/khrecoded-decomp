#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CameraOffsetSource {
    VecFx32 position;
    VecFx32 offset;
} CameraOffsetSource;

extern const s16 data_02053580[];
extern u16 GetBiasAdjustedField(int playerIndex);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

void Camera_ComputeHeadingOffset(const CameraOffsetSource *source, s32 unused, VecFx32 *out)
{
    MtxFx33 rotation;
    VecFx32 offset;
    int index = GetBiasAdjustedField(0) >> 4;

    MTX_RotY33_(&rotation, data_02053580[(0x400 - index) & 0xfff], data_02053580[index]);
    if (source != NULL) {
        MTX_MultVec33(&source->offset, &rotation, out);
        return;
    }
    offset = MakeVec(0, 0x1333, 0);
    MTX_MultVec33(&offset, &rotation, out);
}
