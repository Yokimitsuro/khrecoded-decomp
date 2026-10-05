#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ActorAlphaCommand {
    ScriptOperand operands[4];
    s32 unk_20;
    s32 framesRemaining;
} ActorAlphaCommand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(void *context, int value);
extern void ScriptCmd_SetElemField(void *context, ActorAlphaCommand *command);
extern void SetActorModelAlpha(int actorId, int alpha, BOOL translucent);

int ScriptCmd_SetActorAlpha(void *context, ActorAlphaCommand *command)
{
    int actorId;
    int duration;
    fx32 alpha;

    actorId = ScriptVm_ReadOperandInt(context, &command->operands[0]);
    duration = ScriptVm_ReadOperandInt(context, &command->operands[3]);
    alpha = ScriptVm_ReadOperandFx32(context, &command->operands[1]);
    actorId = ScriptCmd_ReturnValue(context, actorId);
    SetActorModelAlpha(actorId, alpha >> 12, duration != 0);
    if (duration == 0) {
        return 1;
    }
    command->operands[0].value = actorId;
    command->framesRemaining = duration;
    ScriptCmd_SetElemField(context, command);
    return 0;
}
