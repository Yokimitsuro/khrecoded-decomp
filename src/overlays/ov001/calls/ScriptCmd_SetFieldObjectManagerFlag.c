#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern void func_ov001_0206e5a4(u32 value);

int ScriptCmd_SetFieldObjectManagerFlag(void *context, ScriptOperand *operands)
{
    int enabled;

    enabled = ScriptVm_ReadOperandInt(context, operands);
    func_ov001_0206e5a4(enabled != 0);
    return 1;
}
