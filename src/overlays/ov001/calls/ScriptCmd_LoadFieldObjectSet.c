#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern s32 func_ov001_02063a38(void);
extern void QueueFieldUpdate(int setIndex);

int ScriptCmd_LoadFieldObjectSet(void *context, ScriptOperand *operands)
{
    int setIndex;

    setIndex = ScriptVm_ReadOperandInt(context, operands);
    if (func_ov001_02063a38() != 6) {
        QueueFieldUpdate(setIndex);
    }
    return 1;
}
