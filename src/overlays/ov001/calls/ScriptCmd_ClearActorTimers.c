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
extern void ClearActorTimerFields(void *actor);

int ScriptCmd_ClearActorTimers(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;

    actorId = ScriptVm_ReadOperandInt(context, operands);
    actorId = ScriptCmd_ReturnValue(context, actorId);
    ClearActorTimerFields(context->scene->actorObjects[actorId]);
    return 1;
}
