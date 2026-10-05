#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
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

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern u32 ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern void ActorSlot_SetFlag8ByIndex(u16 index, int flag);
extern void ActorObject_SetFlagBit3IfBit14Set(Actor *actor, int enable);

int ScriptCmd_HideActor(ScriptContext *context, ScriptOperand *operands)
{
    u32 actorId;
    Actor *actor;

    actorId = ScriptCmd_ReturnValue(context, ScriptVm_ReadOperandInt(context, operands));
    ActorSlot_SetFlag8ByIndex(actorId, 0);
    actor = context->scene->actorObjects[actorId];
    if (actor != NULL && (actor->unk_D18 != 0 || (actor->flags & 0x4000) != 0)) {
        ActorObject_SetFlagBit3IfBit14Set(actor, 0);
    }
    return 1;
}
