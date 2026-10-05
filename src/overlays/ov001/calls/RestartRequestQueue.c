#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x24];
    u8 stateFlags;
    u8 pad_025[0x1F];
    s32 queuedCount;
    u8 pad_048[0x8];
    u32 isDirty : 1;
    u8 pad_054[0x72];
    u16 idLow;
    u16 idHigh;
    u8 pad_0CA[0x5A];
    s32 progress124;
    u8 pad_128[0x18];
    s32 progress140;
} SceneContext;

extern SceneContext *data_ov001_020a04cc;

extern void *GetSceneTagTracker(void);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b7f80(void *pool, void *record, int invoke);
extern void RefreshGaugeDisplay(void);
extern void RelayoutGaugeRows(void);

void RestartRequestQueue(u16 idHigh, u32 idLow)
{
    SceneContext *ctx = data_ov001_020a04cc;
    int i;
    void *pool;
    int pairCount;

    pool = GetSceneTagTracker();

    if (idLow > 0x1a90) {
        idLow = 0x1a90;
    }
    pairCount = (ctx->queuedCount + 1) / 2;
    for (i = 0; i < pairCount; i++) {
        func_ov027_020b7f80(pool, FindActiveRecordById(pool, (u16)(i + 50000)), 1);
    }
    ctx->queuedCount = 0;
    ctx->isDirty = 1;
    ctx->idLow = idLow;
    ctx->idHigh = idHigh;
    ctx->progress124 = 0;
    ctx->progress140 = 0;
    RefreshGaugeDisplay();
    RelayoutGaugeRows();
    ctx->stateFlags |= 2;
}
