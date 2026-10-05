#include "nitro/types.h"

typedef struct MtxFx43 {
    s32 value[12];
} MtxFx43;

typedef struct JointMatrixCache {
    u8 pad000[0x398];
    u32 slotIds[2];
    MtxFx43 matrices[2];
} JointMatrixCache;

typedef struct RenderOwner {
    u8 pad00[0x2c];
    JointMatrixCache *matrixCache;
} RenderOwner;

typedef struct RenderContext {
    u8 pad00[4];
    RenderOwner *owner;
    u32 flags;
    u8 pad0c[0xae - 0x0c];
    u8 selectedSlot;
} RenderContext;

extern void NNS_G3dGetCurrentMtx(MtxFx43 *position, void *vector);

void CaptureSelectedJointMtx(RenderContext *context)
{
    JointMatrixCache *cache = context->owner->matrixCache;
    u32 selected = (context->flags & 0x10) ? context->selectedSlot : 0xFFFFFFFF;
    int index;

    for (index = 0; index < 2; index++) {
        if (selected == cache->slotIds[index]) {
            NNS_G3dGetCurrentMtx(&cache->matrices[index], NULL);
            return;
        }
    }
}