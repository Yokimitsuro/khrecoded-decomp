#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern int ScriptVm_ReadOperandFx32(void *context, ScriptOperand *operand);
extern void func_ov001_02063d4c(int parameterId, int value);

int ScriptCmd_SetFieldParameter(void *context, ScriptOperand *operands)
{
    int parameterId;
    int value;

    parameterId = ScriptVm_ReadOperandInt(context, operands);
    if (parameterId == 6) {
        value = ScriptVm_ReadOperandFx32(context, operands + 1);
    } else {
        value = ScriptVm_ReadOperandInt(context, operands + 1);
    }
    func_ov001_02063d4c(parameterId, value);
    return 1;
}
