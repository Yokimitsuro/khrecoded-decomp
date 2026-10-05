#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ActorNode {
    u32 flags;
    u16 flags_004;
    u8 pad_006[0x7a];
    u16 angle;
} ActorNode;

typedef struct Actor {
    u8 pad_000[0xd18];
    void *unk_D18;
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
extern fx32 ScriptVm_ReadOperandFx32(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern void *ByteCode_ResolveOperand(ScriptContext *context, ScriptOperand *operand);
extern ActorNode *ActorRegistry_GetEntityByIndex(u16 actorId);
extern void *GetActorRegistry(void);
extern int _s32_div_f(int numerator, int denominator);
extern void Obj_SetPosition(ActorNode *node, const VecFx32 *position);
extern int ProjectPositionDownward(void *model, void *key, VecFx32 *out);
extern void func_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int CollModel_GetEntryField14(void *model, void *key);
extern void func_ov001_0208a480(Actor *actor);
extern void ActorObject_SynchronizeConvertedParameter(Actor *actor, int angle);
extern void func_02038e80(void *link, int mode);

int ScriptCmd_PlaceActor_0208e114(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    ActorNode *node;
    Actor *actor;
    int angle;
    void *key;
    VecFx32 offset;
    VecFx32 ground;

    actorId = ScriptVm_ReadOperandInt(context, operands);
    node = ActorRegistry_GetEntityByIndex(actorId);
    actorId = ScriptCmd_ReturnValue(context, actorId);
    actor = context->scene->actorObjects[actorId];
    if (actor != NULL && (actor->unk_D18 != NULL || (actor->flags & 0x4000) != 0)) {
        func_ov001_0208a480(actor);
    }
    offset.x = ScriptVm_ReadOperandFx32(context, &operands[2]);
    offset.y = ScriptVm_ReadOperandFx32(context, &operands[3]);
    offset.z = ScriptVm_ReadOperandFx32(context, &operands[4]);
    if (operands[1].type == 0) {
        u16 heading;
        heading = _s32_div_f(ScriptVm_ReadOperandInt(context, &operands[5]) << 16, 360);
        Obj_SetPosition(node, &offset);
        actor = context->scene->actorObjects[actorId];
        if (actor != NULL && (actor->unk_D18 != NULL || (actor->flags & 0x4000) != 0)) {
            ActorObject_SynchronizeConvertedParameter(actor, heading);
        } else if ((node->flags & 0x20) == 0) {
            node->angle = heading;
            node->flags_004 |= 0x20;
        }
    } else {
        key = ByteCode_ResolveOperand(context, &operands[1]);
        if (ProjectPositionDownward(GetActorRegistry(), key, &ground)) {
            func_01ff9e0c(&ground, &offset, &ground);
            Obj_SetPosition(node, &ground);
            angle = CollModel_GetEntryField14(GetActorRegistry(), key);
        } else {
            Obj_SetPosition(node, &offset);
        }
        actor = context->scene->actorObjects[actorId];
        if (actor != NULL && (actor->unk_D18 != NULL || (actor->flags & 0x4000) != 0)) {
            ActorObject_SynchronizeConvertedParameter(actor, angle);
        } else if ((node->flags & 0x20) == 0) {
            node->angle = angle;
            node->flags_004 |= 0x20;
        }
    }
    actor = context->scene->actorObjects[actorId];
    if (actor != NULL && (actor->unk_D18 != NULL || (actor->flags & 0x4000) != 0)) {
        func_02038e80(actor->unk_D18, 0);
    }
    return 1;
}
