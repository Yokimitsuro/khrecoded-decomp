#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *context, ScriptOperand *operand);
extern u32 ScriptCmd_ReturnValue(void *context, int value);
extern void ActorSlot_SetField1C4ByIndex(u32 actorId, s32 rate);

int ScriptCmd_SetActorPlaybackRate(void *context, ScriptOperand *operands)
{
    int actorId;
    fx32 rate;

    actorId = ScriptVm_ReadOperandInt(context, operands);
    rate = ScriptVm_ReadOperandFx32(context, operands + 1);
    ActorSlot_SetField1C4ByIndex(ScriptCmd_ReturnValue(context, actorId) & 0xffff, (s16)rate);
    return 1;
}
