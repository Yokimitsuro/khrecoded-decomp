#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct BrightnessFade {
    int startLevel;
    int endLevel;
    int duration;
    int currentLevel;
    int elapsed;
} BrightnessFade;

typedef struct ScriptSceneData {
    u8 pad_00[0x10];
    BrightnessFade fades[2];
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
    u8 pad_1CC[0x628 - 0x1cc];
    int skipRequested;
} ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern void SetBrightnessAndSyncMain(int value);
extern void SetSecondaryBrightness(int value);
extern int _s32_div_f(int dividend, int divisor);

int ScriptCmd_UpdateBrightnessFade(ScriptContext *context, ScriptOperand *operands, int screen)
{
    BrightnessFade *fade;
    int start;
    int elapsed;

    fade = &context->scene->fades[screen];
    if (context->skipRequested != 0) {
        fade->currentLevel = ScriptVm_ReadOperandInt(context, operands) - 0x10;
        return 1;
    }
    elapsed = ++fade->elapsed;
    start = fade->startLevel;
    fade->currentLevel = start + _s32_div_f(elapsed * (fade->endLevel - start), fade->duration);
    if (fade->currentLevel > 0x10) {
        fade->currentLevel = 0x10;
    }
    if (fade->currentLevel < -0x10) {
        fade->currentLevel = -0x10;
    }
    if (screen == 0) {
        SetBrightnessAndSyncMain(fade->currentLevel);
    } else {
        SetSecondaryBrightness(fade->currentLevel);
    }
    if (fade->elapsed >= fade->duration) {
        return 1;
    }
    return 0;
}
