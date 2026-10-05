#include "nitro/types.h"

typedef struct SceneContext {
    void *table;
    void *messages;
    u8 pad_08[4];
    s8 nextId;
    s8 currentId;
    s8 previousId;
    u8 pad_0f[0x10c0 - 0xf];
    s8 pendingId;
    u8 pad_10c1[0x10f4 - 0x10c1];
} SceneContext;

extern SceneContext *data_ov001_020a048c;
extern char sOv001_MiWdWdmdl_0209eaa0[];
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MIi_CpuClearFast(u32 value, void *dest, u32 size);
extern void *Msg_OpenContainerAndReadHeader(const char *path, int mode, int flags);

void CreateSceneContext(void)
{
    SceneContext *ctx = NNSi_FndAllocFromDefaultHeap(sizeof(SceneContext));

    data_ov001_020a048c = ctx;
    MIi_CpuClearFast(0, ctx, sizeof(SceneContext));
    ctx->nextId = -1;
    ctx->currentId = -1;
    ctx->previousId = -1;
    ctx->pendingId = -1;
    ctx->messages = Msg_OpenContainerAndReadHeader(sOv001_MiWdWdmdl_0209eaa0, 2, 0);
}
