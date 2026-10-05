#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern void ConfigureMenuPanel(int gimmickId, u16 flags, int stateA, int stateB, BOOL refresh);

int ScriptCmd_SetMapGimmickFlags(void *context, ScriptOperand *operands)
{
    int gimmickId;
    u32 flags;
    int refresh;

    gimmickId = ScriptVm_ReadOperandInt(context, operands);
    flags = ScriptVm_ReadOperandInt(context, operands + 1);
    refresh = ScriptVm_ReadOperandInt(context, operands + 2);
    ConfigureMenuPanel(gimmickId, flags, -1, -1, refresh);
    return 1;
}
