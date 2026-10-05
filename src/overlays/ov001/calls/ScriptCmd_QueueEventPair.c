#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern void QueueEventPair(u16 first, u16 second);

int ScriptCmd_QueueEventPair(void *context, ScriptOperand *operands)
{
    u32 first;
    u32 second;

    first = ScriptVm_ReadOperandInt(context, operands);
    second = ScriptVm_ReadOperandInt(context, operands + 1);
    QueueEventPair(first, second);
    return 1;
}
