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
extern void func_ov001_020889f8(u32 colorIndex, u32 alpha);

int ScriptCmd_StartScreenOverlayFade(void *context, OverlayFadeCommand *command)
{
    u32 colorIndex;
    fx32 targetAlpha;
    int duration;

    colorIndex = ScriptVm_ReadOperandInt(context, &command->operands[0]);
    ScriptVm_ReadOperandFx32(context, &command->operands[1]);
    targetAlpha = ScriptVm_ReadOperandFx32(context, &command->operands[2]);
    duration = ScriptVm_ReadOperandInt(context, &command->operands[3]);
    if (duration == 0) {
        func_ov001_020889f8(colorIndex, targetAlpha >> 12);
        return 1;
    }
    command->framesRemaining = duration;
    ScriptCmd_SetElemField(context, command);
    return 0;
}
