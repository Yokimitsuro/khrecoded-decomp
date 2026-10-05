#include "nitro/types.h"

typedef struct SceneSlot {
    u8 node[0x104];
    u8 flags;
    u8 pad_105[3];
} SceneSlot;

typedef struct SceneContext {
    u8 pad_00[0x18];
    SceneSlot slots[16];
} SceneContext;

extern SceneContext *data_ov001_020a048c;
extern void func_01ffb12c(void *node);

void DrawVisibleSceneSlots(void) {
    SceneContext *ctx = data_ov001_020a048c;
    s32 i;

    for (i = 0; i < 16; i++) {
        SceneSlot *slot = &ctx->slots[i];
        if ((slot->flags & 1) && (slot->flags & 0x80)) {
            func_01ffb12c(slot);
        }
    }
}
