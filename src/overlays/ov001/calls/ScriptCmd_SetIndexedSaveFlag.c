#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern void func_ov001_0206943c(s32 index, s32 useSecondSet, s32 clearFlag);

int ScriptCmd_SetIndexedSaveFlag(void *context, ScriptOperand *operands)
{
    int useSecondSet;
    int index;
    int clearFlag;

    useSecondSet = ScriptVm_ReadOperandInt(context, operands);
    index = ScriptVm_ReadOperandInt(context, operands + 1);
    clearFlag = ScriptVm_ReadOperandInt(context, operands + 2);
    func_ov001_0206943c(index, useSecondSet, clearFlag != 0);
    return 1;
}
