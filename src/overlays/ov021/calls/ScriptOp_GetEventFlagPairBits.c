#include "nitro/types.h"

typedef struct ScriptContext {
    u8 pad_00[0x2c];
    u16 resultTag;
    u16 pad_2e;
    s32 resultValue;
} ScriptContext;

extern BOOL func_ov001_020645c8(u32 flagId);

int ScriptOp_GetEventFlagPairBits(ScriptContext *context)
{
    u32 bits = 0;
    BOOL first;
    BOOL second;

    context->resultTag = 1;
    first = func_ov001_020645c8(0x3716);
    second = func_ov001_020645c8(0x3717);
    if (first) {
        bits |= 1;
    }
    if (second) {
        bits |= 2;
    }
    context->resultValue = bits;
    return 0;
}
