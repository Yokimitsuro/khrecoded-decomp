#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern BOOL func_ov036_020bd560(int screen);

BOOL ScriptCmd_WaitScreenLayerIdle(void *context, ScriptOperand *operands)
{
    if (!func_ov036_020bd560(ScriptVm_ReadOperandInt(context, operands))) {
        return TRUE;
    }
    return FALSE;
}
