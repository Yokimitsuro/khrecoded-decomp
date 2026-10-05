#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct FlagTaskParams {
    int first;
    int second;
    u8 lowByte;
    u8 highByte;
    u8 pad[6];
} FlagTaskParams;

typedef struct ScriptContext ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern void func_ov001_02069274(int target, BOOL enable, int kind, FlagTaskParams *params);

BOOL ScriptCmd_QueueFlagTaskKind1(ScriptContext *context, ScriptOperand *operands)
{
    int enable;
    int target;
    FlagTaskParams params;

    enable = ScriptVm_ReadOperandInt(context, &operands[0]);
    target = ScriptVm_ReadOperandInt(context, &operands[1]);
    params.first = ScriptVm_ReadOperandInt(context, &operands[2]);
    params.second = ScriptVm_ReadOperandInt(context, &operands[3]);
    params.highByte = ScriptVm_ReadOperandInt(context, &operands[4]);
    params.lowByte = ScriptVm_ReadOperandInt(context, &operands[5]);
    func_ov001_02069274(target, enable != 0, 1, &params);
    return TRUE;
}
