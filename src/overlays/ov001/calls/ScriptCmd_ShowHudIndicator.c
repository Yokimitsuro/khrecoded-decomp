#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern BOOL StartSlotLayoutAnimation(int indicatorKind, u16 frameNumber);
extern BOOL func_ov001_0207d468(u32 value);

int ScriptCmd_ShowHudIndicator(void *context, ScriptOperand *operands)
{
    int indicatorKind;
    u32 frameNumber;

    indicatorKind = ScriptVm_ReadOperandInt(context, operands);
    frameNumber = ScriptVm_ReadOperandInt(context, operands + 1);
    StartSlotLayoutAnimation(indicatorKind, frameNumber);
    func_ov001_0207d468(1);
    return 0;
}
