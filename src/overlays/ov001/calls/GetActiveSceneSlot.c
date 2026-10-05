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

SceneSlot *GetActiveSceneSlot(s32 index) {
    SceneContext *ctx = data_ov001_020a048c;

    if (ctx->slots[index].flags & 0x80) {
        return &ctx->slots[index];
    }
    return NULL;
}
