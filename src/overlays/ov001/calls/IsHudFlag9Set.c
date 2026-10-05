#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x480];
    u32 unk_bits0 : 9;
    u32 flag9 : 1;
    u32 unk_bits10 : 22;
} HudContext;

typedef struct {
    u32 unk_00;
    HudContext *context;
} HudGlobals;

extern HudGlobals data_ov001_020a04c4;

BOOL IsHudFlag9Set(void) {
    if (data_ov001_020a04c4.context->flag9 == 1) {
        return TRUE;
    }
    return FALSE;
}
