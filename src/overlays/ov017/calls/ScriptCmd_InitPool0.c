#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern void *func_ov017_020a4224(void);
extern void func_ov017_020a413c(void *manager, s32 capacity);

int ScriptCmd_InitPool0(void *vm, ScriptOperand *operands)
{
    int capacity = ScriptVm_ReadOperandInt(vm, operands);

    func_ov017_020a413c(func_ov017_020a4224(), (u16)capacity);
    return 1;
}
