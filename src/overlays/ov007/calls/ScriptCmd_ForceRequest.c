#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *script, ScriptOperand *operand);
extern void func_ov035_020baea4(int requestId, int mode, BOOL force);

int ScriptCmd_ForceRequest(void *script, ScriptOperand *operands)
{
    int requestId = ScriptVm_ReadOperandInt(script, operands);
    int mode = ScriptVm_ReadOperandInt(script, operands + 1);

    func_ov035_020baea4(requestId, mode, TRUE);
    return 1;
}
