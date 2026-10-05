#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void NNS_G3dGeBufferOP_N(u32 command, const void *params, u32 count);
extern void FlushGeometryCommandBuffer(const void *src, u32 size);
extern void FlushActorGeometryBuffer(void);
extern u8 data_ov001_0209e39c[0x2c];

BOOL TranslateAndFlushGeometry(void *actor, fx32 height, BOOL useActorBuffer)
{
    VecFx32 offset;

    offset.x = 0;
    offset.y = FX_Div(height, 0x1800);
    offset.z = 0;
    NNS_G3dGeBufferOP_N(0x1c, &offset, 3);
    if (!useActorBuffer) {
        FlushGeometryCommandBuffer(data_ov001_0209e39c, 0x2c);
    } else {
        FlushActorGeometryBuffer();
    }
    return TRUE;
}
