#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    int base;
    u8 pad_10[0x14];
    int pc;
} ScriptContext;

typedef struct {
    u32 unk_00;
    int active;
} ScriptEntry;

extern ScriptEntry *func_ov021_020b0608(ScriptContext *context, int address);

int ScriptOp_JumpIfEntryInactive(ScriptContext *context, int *operands) {
    if (func_ov021_020b0608(context, context->base + operands[0])->active == 0) {
        context->pc = operands[1];
        return 2;
    }
    return 0;
}
