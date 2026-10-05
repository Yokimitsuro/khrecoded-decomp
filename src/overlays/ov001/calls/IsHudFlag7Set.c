#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x480];
    u32 unk_bits0 : 7;
    u32 flag7 : 1;
    u32 unk_bits8 : 24;
} HudContext;

typedef struct {
    u32 unk_00;
    HudContext *context;
} HudGlobals;

extern HudGlobals data_ov001_020a04c4;

BOOL IsHudFlag7Set(void) {
    if (data_ov001_020a04c4.context->flag7 == 1) {
        return TRUE;
    }
    return FALSE;
}
