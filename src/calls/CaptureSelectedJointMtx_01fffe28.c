#include "nitro/types.h"

typedef struct MtxFx43 {
    s32 value[12];
} MtxFx43;

typedef struct JointMatrixCache {
    u8 pad_000[0x6bc];
    u32 slotIds[3];
    u8 pad_6c8[4];
    MtxFx43 matrices[3];
} JointMatrixCache;

typedef struct RenderContext {
    u8 pad_00[8];
    u32 flags;
    u8 pad_0c[0xae - 0x0c];
    u8 selectedSlot;
} RenderContext;

extern void NNS_G3dGetCurrentMtx(void *position, void *vector);

void CaptureSelectedJointMtx_01fffe28(JointMatrixCache *cache, RenderContext *context) {
    u32 selected;
    int index;

    selected = (context->flags & 0x10) != 0 ? context->selectedSlot : (u32)-1;
    index = 0;
    do {
        if (selected == cache->slotIds[index]) {
            NNS_G3dGetCurrentMtx(&cache->matrices[index], NULL);
            return;
        }
        index++;
    } while (index < 3);
}
