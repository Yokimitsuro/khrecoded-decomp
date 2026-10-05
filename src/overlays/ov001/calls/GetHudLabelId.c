#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x6ec];
    s32 labelIds[4];
} HudContext;

typedef struct {
    u32 unk_00;
    HudContext *context;
} HudGlobals;

extern HudGlobals data_ov001_020a04c4;

s32 GetHudLabelId(int labelIndex) {
    return data_ov001_020a04c4.context->labelIds[labelIndex];
}
