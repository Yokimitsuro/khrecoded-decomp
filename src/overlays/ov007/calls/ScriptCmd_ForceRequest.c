#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *script, ScriptOperand *operand);
extern void RequestSceneEvent(int requestId, int mode, BOOL force);

int ScriptCmd_ForceRequest(void *script, ScriptOperand *operands)
{
    int requestId = ScriptVm_ReadOperandInt(script, operands);
    int mode = ScriptVm_ReadOperandInt(script, operands + 1);

    RequestSceneEvent(requestId, mode, TRUE);
    return 1;
}
