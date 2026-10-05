#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern void ActorChannel_SetStateFields(u32 state, u32 enabled);

int ScriptCmd_SetActorChannelState(void *context, ScriptOperand *operands)
{
    u32 state;
    int enabled;

    state = ScriptVm_ReadOperandInt(context, operands);
    enabled = ScriptVm_ReadOperandInt(context, operands + 1);
    ActorChannel_SetStateFields(state, enabled != 0);
    return 1;
}
