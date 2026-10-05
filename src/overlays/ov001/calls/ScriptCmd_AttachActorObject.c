#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ActorObject {
    u8 pad_000[0xef4];
    u32 flags;
} ActorObject;

typedef struct ScriptSceneData {
    u8 pad_00[0x4c];
    ActorObject **actorObjects;
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
} ScriptContext;

typedef struct ActorNode {
    u8 pad_00[0xa8];
    u8 position[12];
} ActorNode;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern void AllocateSlotIfNull(ScriptContext *context, int index);
extern void *GetEntryFieldForMode(int partyIndex);
extern void Actor_AttachSource(ActorObject *actor, int mode, void *source);
extern ActorNode *ActorRegistry_GetEntityByIndex(u16 actorId);
extern void SpawnActorModelAt(ActorObject *actor, int mode, void *position, int actorId);

int ScriptCmd_AttachActorObject(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;

    actorId = ScriptVm_ReadOperandInt(context, operands);
    actorId = ScriptCmd_ReturnValue(context, actorId);
    AllocateSlotIfNull(context, actorId);
    if (actorId < 3) {
        Actor_AttachSource(context->scene->actorObjects[actorId], actorId, GetEntryFieldForMode(actorId));
    } else {
        ActorNode *node = ActorRegistry_GetEntityByIndex(actorId);
        SpawnActorModelAt(context->scene->actorObjects[actorId], 0, node->position, actorId);
    }
    context->scene->actorObjects[actorId]->flags |= 0x10000;
    return 1;
}
