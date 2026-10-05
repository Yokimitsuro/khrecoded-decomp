#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptSceneData {
    u8 pad_00[0x4c];
    void **actorObjects;
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
} ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern int _s32_div_f(int dividend, int divisor);
extern void SetActorFieldEfc(void *actor, u32 targetHeading);

int ScriptCmd_SetActorHeadingDegrees(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    int degrees;
    u16 heading;

    actorId = ScriptVm_ReadOperandInt(context, operands);
    degrees = ScriptVm_ReadOperandInt(context, operands + 1);
    actorId = ScriptCmd_ReturnValue(context, actorId);
    heading = _s32_div_f(degrees << 16, 360);
    SetActorFieldEfc(context->scene->actorObjects[actorId], heading);
    return 1;
}
