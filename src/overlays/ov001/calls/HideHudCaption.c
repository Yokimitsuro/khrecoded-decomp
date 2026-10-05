#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1c];
    u8 recordPool[0x2e4 - 0x1c];
    u64 captionTick;
} HudContext;

typedef struct {
    u32 unk_00;
    HudContext *context;
} HudGlobals;

extern HudGlobals data_ov001_020a04c4;

extern void *func_ov027_020b81a4(void *pool, u32 recordId);
extern void func_ov027_020b8288(void *pool, void *record);

void HideHudCaption(void) {
    HudContext *context = data_ov001_020a04c4.context;
    func_ov027_020b8288(context->recordPool, func_ov027_020b81a4(context->recordPool, 6));
    context->captionTick = 0;
}
