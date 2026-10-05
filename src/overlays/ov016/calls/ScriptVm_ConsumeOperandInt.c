#include "nitro/types.h"

typedef struct ScriptOperand {
    u8 data[8];
} ScriptOperand;

extern s32 ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);

s32 ScriptVm_ConsumeOperandInt(void *vm, ScriptOperand **cursor)
{
    ScriptOperand *operand = *cursor;

    *cursor = operand + 1;
    return ScriptVm_ReadOperandInt(vm, operand);
}
