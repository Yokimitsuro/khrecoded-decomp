#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    u8 data[8];
} ScriptOperand;

extern fx32 ScriptVm_ReadOperandFx32(void *vm, ScriptOperand *operand);

fx32 ScriptVm_ConsumeOperandFx32(void *vm, ScriptOperand **cursor)
{
    ScriptOperand *operand = *cursor;

    *cursor = operand + 1;
    return ScriptVm_ReadOperandFx32(vm, operand);
}
