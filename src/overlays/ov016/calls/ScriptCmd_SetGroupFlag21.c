#include "nitro/types.h"

typedef struct ScriptOperand {
    u32 type;
    u32 value;
} ScriptOperand;

extern s32 ScriptVm_ConsumeOperandInt(void *vm, ScriptOperand **cursor);
extern int func_ov001_0208722c(void);
extern unsigned int func_ov001_0208723c(int index);
extern void func_ov016_020a6d1c(unsigned int group, BOOL enable);

BOOL ScriptCmd_SetGroupFlag21(void *vm, ScriptOperand *operands)
{
    ScriptOperand *cursor = operands;
    int index;
    BOOL enable;

    index = ScriptVm_ConsumeOperandInt(vm, &cursor);
    enable = ScriptVm_ConsumeOperandInt(vm, &cursor) != 0;
    if (func_ov001_0208722c() > 0) {
        func_ov016_020a6d1c(func_ov001_0208723c(index), enable);
    }
    return TRUE;
}
