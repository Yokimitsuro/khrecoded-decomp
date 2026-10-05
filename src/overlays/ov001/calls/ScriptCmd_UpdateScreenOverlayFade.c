#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct OverlayFadeCommand {
    ScriptOperand operands[4];
    s32 unk_20;
    s32 framesRemaining;
} OverlayFadeCommand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *context, ScriptOperand *operand);
extern void ScriptCmd_SetElemField(void *context, OverlayFadeCommand *command);
extern fx32 EvaluateInterpolationCurve(int curve, u32 duration, int remaining);
extern fx32 ScaleAroundPivot(fx32 progress, fx32 target, fx32 start);
extern void SetManagerCallbackPair(u32 colorIndex, u32 alpha);

int ScriptCmd_UpdateScreenOverlayFade(void *context, OverlayFadeCommand *command)
{
    u32 colorIndex;
    fx32 startAlpha;
    fx32 targetAlpha;
    u32 duration;
    int remaining;
    fx32 progress;
    fx32 alpha;

    colorIndex = ScriptVm_ReadOperandInt(context, &command->operands[0]);
    startAlpha = ScriptVm_ReadOperandFx32(context, &command->operands[1]);
    targetAlpha = ScriptVm_ReadOperandFx32(context, &command->operands[2]);
    duration = ScriptVm_ReadOperandInt(context, &command->operands[3]);
    remaining = command->framesRemaining - 1;
    command->framesRemaining = remaining;
    if (remaining == 0) {
        SetManagerCallbackPair(colorIndex, targetAlpha >> 12);
        return 1;
    }
    progress = EvaluateInterpolationCurve(2, duration, remaining);
    alpha = ScaleAroundPivot(progress, targetAlpha, startAlpha);
    SetManagerCallbackPair(colorIndex, alpha >> 12);
    ScriptCmd_SetElemField(context, command);
    return 0;
}
