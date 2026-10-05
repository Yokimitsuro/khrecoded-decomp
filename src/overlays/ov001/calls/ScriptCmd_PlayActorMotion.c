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
extern void Script_ResolveMotionNameAndId(ScriptContext *context, ScriptOperand *operands, int actorId,
                                                   int *outMotionId, char *outMotionName);
extern void ActivateFreeSlotEntry(void *actor, char *motionName, int motionId, int layer, int mode, int flags);

int ScriptCmd_PlayActorMotion(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    int layer;
    int mode;
    int motionId;
    char motionName[64];

    actorId = ScriptVm_ReadOperandInt(context, operands);
    layer = ScriptVm_ReadOperandInt(context, operands + 1);
    mode = ScriptVm_ReadOperandInt(context, operands + 4);
    motionId = -1;
    actorId = ScriptCmd_ReturnValue(context, actorId);
    motionName[0] = '\0';
    Script_ResolveMotionNameAndId(context, operands, actorId, &motionId, motionName);
    ActivateFreeSlotEntry(context->scene->actorObjects[actorId], motionName, motionId, layer, mode, 0);
    return 1;
}
