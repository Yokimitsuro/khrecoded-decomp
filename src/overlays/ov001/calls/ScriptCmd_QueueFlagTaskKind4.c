#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptContext ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern void func_ov001_02069274(int target, BOOL enable, int kind, int *values);

BOOL ScriptCmd_QueueFlagTaskKind4(ScriptContext *context, ScriptOperand *operands)
{
    int enable;
    int target;
    int values[4];

    enable = ScriptVm_ReadOperandInt(context, &operands[0]);
    target = ScriptVm_ReadOperandInt(context, &operands[1]);
    values[0] = ScriptVm_ReadOperandInt(context, &operands[2]);
    values[1] = ScriptVm_ReadOperandInt(context, &operands[3]);
    values[2] = ScriptVm_ReadOperandInt(context, &operands[4]);
    values[3] = ScriptVm_ReadOperandInt(context, &operands[5]);
    func_ov001_02069274(target, enable != 0, 4, values);
    return TRUE;
}
