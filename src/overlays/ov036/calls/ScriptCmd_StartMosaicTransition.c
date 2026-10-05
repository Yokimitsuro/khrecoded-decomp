#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern void func_ov036_020bd820(int reveal, int duration);
extern void ScriptCmd_SetElemField(void *context, u32 value);

int ScriptCmd_StartMosaicTransition(void *context, ScriptOperand *operands)
{
    int reveal = ScriptVm_ReadOperandInt(context, &operands[0]);
    int duration = ScriptVm_ReadOperandInt(context, &operands[1]);

    func_ov036_020bd820(reveal, duration);
    ScriptCmd_SetElemField(context, (u32)operands);
    return 0;
}
