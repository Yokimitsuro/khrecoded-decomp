#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern void *func_ov017_020a4224(void);
extern void func_ov017_020a424c(void *manager, u32 value);

int ScriptCmd_SetManagerValue(void *vm, ScriptOperand *operands)
{
    int value = ScriptVm_ReadOperandInt(vm, operands);

    func_ov017_020a424c(func_ov017_020a4224(), value);
    return 1;
}
