#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern u32 SubScene9_Request(u8 value);

BOOL ScriptCmd_RequestSubScene9(void *context, ScriptOperand *operands)
{
    int waitForScene;

    waitForScene = ScriptVm_ReadOperandInt(context, operands);
    SubScene9_Request(0);
    return waitForScene == 0;
}
