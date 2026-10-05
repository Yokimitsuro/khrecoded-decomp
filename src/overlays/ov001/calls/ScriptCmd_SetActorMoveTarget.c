#include "nitro/types.h"
#include "nitro/fx_types.h"

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
extern fx32 ScriptVm_ReadOperandFx32(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern void ResolveScriptTargetPosition(ScriptContext *context, ScriptOperand *operands, int actorId, VecFx32 *target);
extern void SetTargetPosition(void *actor, VecFx32 *target, fx32 speed, int duration);
extern void SetActorFlagBit4(void *actor, s32 enable);

int ScriptCmd_SetActorMoveTarget(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    int duration;
    fx32 speed;
    VecFx32 target;

    actorId = ScriptVm_ReadOperandInt(context, operands);
    duration = ScriptVm_ReadOperandInt(context, operands + 7);
    speed = ScriptVm_ReadOperandFx32(context, operands + 5);
    ScriptVm_ReadOperandFx32(context, operands + 6);
    actorId = ScriptCmd_ReturnValue(context, actorId);
    ResolveScriptTargetPosition(context, operands, actorId, &target);
    SetTargetPosition(context->scene->actorObjects[actorId], &target, speed, duration);
    if (operands[8].type != 0) {
        SetActorFlagBit4(context->scene->actorObjects[actorId], 0);
    } else {
        SetActorFlagBit4(context->scene->actorObjects[actorId], 1);
    }
    return 1;
}
