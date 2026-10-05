#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern void UpdateGroupItemStats(int gimmickId, int secondaryState, int primaryState);

int ScriptCmd_SetMapGimmickState(void *context, ScriptOperand *operands)
{
    int gimmickId;
    int primaryState;
    int secondaryState;

    gimmickId = ScriptVm_ReadOperandInt(context, operands);
    primaryState = ScriptVm_ReadOperandInt(context, operands + 1);
    secondaryState = ScriptVm_ReadOperandInt(context, operands + 2);
    UpdateGroupItemStats(gimmickId, secondaryState, primaryState);
    return 1;
}
