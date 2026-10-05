#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern void DispatchPartyEntryArgByMode(int entityIndex, BOOL enabled);

int ScriptCmd_SetEntityFlag(void *context, ScriptOperand *operands)
{
    int entityIndex;
    int enabled;

    entityIndex = ScriptVm_ReadOperandInt(context, operands);
    enabled = ScriptVm_ReadOperandInt(context, operands + 1);
    DispatchPartyEntryArgByMode(entityIndex, enabled != 0);
    return 1;
}
