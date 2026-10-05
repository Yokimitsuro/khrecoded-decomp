#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct Actor {
    u8 pad_000[0xd18];
    u32 unk_D18;
    u8 pad_D1C[0x1d8];
    u32 flags;
} Actor;

typedef struct ScriptSceneData {
    u8 pad_00[0x4c];
    Actor **actorObjects;
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
} ScriptContext;

typedef struct ActorNode {
    u8 pad_00[4];
    u8 fadeState[0xd8];
    u8 blendTable[4];
} ActorNode;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern void Script_ResolveMotionNameAndId(ScriptContext *context, ScriptOperand *operands, int actorId,
                                                   int *outMotionId, char *outMotionName);
extern void SetActorAnimSlot(Actor *actor, char *motionName, int motionId, int layer, int frameCount);
extern ActorNode *ActorRegistry_GetEntityByIndex(u16 actorId);
extern void BlendToAnimationTrack(void *state, u16 trackIndex, void *table, s16 blendIndex, int frameCount);

int ScriptCmd_PlayActorMotionOrBlend(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    int layer;
    int frameCount;
    int motionId;
    char motionName[64];
    ActorNode *node;

    actorId = ScriptVm_ReadOperandInt(context, operands);
    layer = ScriptVm_ReadOperandInt(context, operands + 1);
    frameCount = ScriptVm_ReadOperandInt(context, operands + 4);
    motionId = -1;
    actorId = ScriptCmd_ReturnValue(context, actorId);
    if (context->scene->actorObjects[actorId] != NULL
        && (context->scene->actorObjects[actorId]->unk_D18 != 0
            || (context->scene->actorObjects[actorId]->flags & 0x4000) != 0)) {
        motionName[0] = '\0';
        Script_ResolveMotionNameAndId(context, operands, actorId, &motionId, motionName);
        SetActorAnimSlot(context->scene->actorObjects[actorId], motionName, motionId, layer, frameCount);
    } else {
        node = ActorRegistry_GetEntityByIndex(actorId);
        motionId = ScriptVm_ReadOperandInt(context, operands + 3);
        BlendToAnimationTrack(node->fadeState, layer, node->blendTable, motionId, frameCount);
    }
    return 1;
}
