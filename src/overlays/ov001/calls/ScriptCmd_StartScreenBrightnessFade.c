#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScreenFade {
    s32 startLevel;
    s32 targetLevel;
    s32 duration;
    s32 currentLevel;
    s32 elapsed;
} ScreenFade;

typedef struct ScriptSceneData {
    u8 pad_00[0x10];
    ScreenFade fades[2];
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
    u8 pad_1cc[0x628 - 0x1cc];
    s32 isSkipping;
} ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern int func_02029f5c(void);
extern int func_02029f6c(void);
extern void SetBrightnessAndSyncMain(int value);
extern void SetSecondaryBrightness(int value);
extern void GXx_SetMasterBrightness_(u16 *reg, int value);

void ScriptCmd_StartScreenBrightnessFade(ScriptContext *context, ScriptOperand *operands, int screen)
{
    ScreenFade *fade;
    int duration;
    int level;

    fade = &context->scene->fades[screen];
    if (context->isSkipping != 0) {
        fade->currentLevel = ScriptVm_ReadOperandInt(context, operands) - 16;
        return;
    }
    fade->elapsed = 0;
    fade->targetLevel = ScriptVm_ReadOperandInt(context, operands) - 16;
    duration = ScriptVm_ReadOperandInt(context, operands + 1);
    fade->duration = duration;
    fade->currentLevel = fade->targetLevel;
    if (duration > 0) {
        if (screen == 0) {
            level = func_02029f5c();
        } else {
            level = func_02029f6c();
        }
        fade->currentLevel = level;
        fade->startLevel = level;
    }
    if (screen == 0) {
        SetBrightnessAndSyncMain(fade->currentLevel);
        GXx_SetMasterBrightness_((u16 *)0x0400006c, fade->currentLevel);
        return;
    }
    SetSecondaryBrightness(fade->currentLevel);
    GXx_SetMasterBrightness_((u16 *)0x0400106c, fade->currentLevel);
}
