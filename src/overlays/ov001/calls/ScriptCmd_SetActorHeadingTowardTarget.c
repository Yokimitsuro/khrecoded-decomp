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
extern ScriptOperand *ScriptVm_ResolveOperand(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern u32 ComputeHeadingToScriptTarget(ScriptContext *context, ScriptOperand *target, int actorId);
extern void SetActorFieldEfc(void *actor, u32 targetHeading);

int ScriptCmd_SetActorHeadingTowardTarget(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    ScriptOperand *target;
    u32 heading;

    actorId = ScriptVm_ReadOperandInt(context, operands);
    target = ScriptVm_ResolveOperand(context, operands + 1);
    actorId = ScriptCmd_ReturnValue(context, actorId);
    heading = ComputeHeadingToScriptTarget(context, target, actorId);
    SetActorFieldEfc(context->scene->actorObjects[actorId], heading);
    return 1;
}
