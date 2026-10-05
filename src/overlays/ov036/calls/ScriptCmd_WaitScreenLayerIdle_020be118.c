#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern BOOL IsScreenLayerLoaded(int screen);

BOOL ScriptCmd_WaitScreenLayerIdle_020be118(void *context, ScriptOperand *operands)
{
    if (!IsScreenLayerLoaded(ScriptVm_ReadOperandInt(context, operands))) {
        return TRUE;
    }
    return FALSE;
}
