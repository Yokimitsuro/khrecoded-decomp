#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x484];
    s32 unk_484;
} HudContext;

typedef struct {
    u32 unk_00;
    HudContext *context;
} HudGlobals;

extern HudGlobals data_ov001_020a04c4;

extern void func_ov001_020701a8(HudContext *context);

void FlushHudWidgetAndSetState(s32 value) {
    HudContext *context = data_ov001_020a04c4.context;
    func_ov001_020701a8(context);
    context->unk_484 = value;
}
