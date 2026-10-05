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
extern void *ActorRegistry_GetEntityByIndex(u16 actorId);
extern fx32 EvaluateInterpolationCurve(int curveType, u32 duration, int framesRemaining);
extern fx32 ScaleAroundPivot(fx32 progress, fx32 target, fx32 start);
extern void SetActorModelAlpha(int actorId, int alpha, BOOL translucent);
extern void ScriptCmd_SetElemField(void *context, ActorAlphaCommand *command);

int ScriptCmd_UpdateActorAlphaFade(void *context, ActorAlphaCommand *command)
{
    int actorId;
    int duration;
    fx32 startAlpha;
    fx32 targetAlpha;
    fx32 progress;

    actorId = ScriptVm_ReadOperandInt(context, &command->operands[0]);
    duration = ScriptVm_ReadOperandInt(context, &command->operands[3]);
    startAlpha = ScriptVm_ReadOperandFx32(context, &command->operands[1]);
    targetAlpha = ScriptVm_ReadOperandFx32(context, &command->operands[2]);
    ActorRegistry_GetEntityByIndex(actorId);
    if (--command->framesRemaining == 0) {
        SetActorModelAlpha(actorId, targetAlpha >> 12, FALSE);
        return 1;
    }
    progress = EvaluateInterpolationCurve(2, duration, command->framesRemaining);
    SetActorModelAlpha(actorId, ScaleAroundPivot(progress, targetAlpha, startAlpha) >> 12, TRUE);
    ScriptCmd_SetElemField(context, command);
    return 0;
}
