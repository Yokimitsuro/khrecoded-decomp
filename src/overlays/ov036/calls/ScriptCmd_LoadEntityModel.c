#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern BOOL func_ov036_020bd1c0(int modelId, int depthSlot);
extern void SetPanelEnabled(u32 value);

BOOL ScriptCmd_LoadEntityModel(void *context, ScriptOperand *operands)
{
    int modelId = ScriptVm_ReadOperandInt(context, &operands[0]);
    int depthSlot = ScriptVm_ReadOperandInt(context, &operands[1]);

    if (func_ov036_020bd1c0(modelId, depthSlot)) {
        SetPanelEnabled(1);
        return TRUE;
    }
    return FALSE;
}
