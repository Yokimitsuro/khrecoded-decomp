#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptWork {
    u8 pad_00[0x70];
    char *strings[16];
} ScriptWork;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptWork *work;
} ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern const char *ByteCode_ResolveOperand(ScriptContext *context, ScriptOperand *operand);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern char *strcpy(char *dst, const char *src);

int ScriptCmd_SetWorkString(ScriptContext *context, ScriptOperand *operands)
{
    int slot;
    const char *text;

    slot = ScriptVm_ReadOperandInt(context, operands);
    text = ByteCode_ResolveOperand(context, operands + 1);
    if (context->work->strings[slot] == NULL) {
        context->work->strings[slot] = NNSi_FndAllocFromDefaultHeap(0x40);
        MI_CpuFill8(context->work->strings[slot], 0, 0x40);
    }
    strcpy(context->work->strings[slot], text);
    return 1;
}
