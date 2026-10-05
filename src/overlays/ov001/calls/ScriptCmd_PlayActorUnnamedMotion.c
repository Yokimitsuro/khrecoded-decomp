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
extern void ActivateFreeSlotEntry(void *actor, char *motionName, int motionId, int layer, int mode, int flags);

int ScriptCmd_PlayActorUnnamedMotion(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    int layer;

    actorId = ScriptVm_ReadOperandInt(context, operands);
    layer = ScriptVm_ReadOperandInt(context, operands + 1);
    actorId = ScriptCmd_ReturnValue(context, actorId);
    ActivateFreeSlotEntry(context->scene->actorObjects[actorId], NULL, -2, layer, 0, 0);
    return 1;
}
