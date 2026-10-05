#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ActorObject ActorObject;

typedef struct ScriptSceneData {
    u8 pad_00[0x4c];
    ActorObject **actorObjects;
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
} ScriptContext;

typedef struct ActorNode {
    u8 pad_00[4];
    u16 flags;
} ActorNode;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern void *ByteCode_ResolveOperand(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern void ActorSlot_AttachToParentByIndex(u16 childIndex, u16 parentIndex, void *attachData);
extern ActorNode *ActorRegistry_GetEntityByIndex(u16 actorId);
extern void AllocateSlotIfNull(ScriptContext *context, int index);
extern void SpawnActorModelAt(ActorObject *actor, int mode, const VecFx32 *position, int actorId);
extern void AttachActorToOwner(ActorObject *actor, ActorObject *owner, u32 actorId);
extern void ActorSlot_SetFlag8ByIndex(u16 index, BOOL enable);
extern const VecFx32 data_0205344c;

int ScriptCmd_AttachActorToParent(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    int parentId;
    int mode;
    void *attachData;

    actorId = ScriptVm_ReadOperandInt(context, operands);
    parentId = ScriptVm_ReadOperandInt(context, operands + 1);
    mode = ScriptVm_ReadOperandInt(context, operands + 3);
    attachData = ByteCode_ResolveOperand(context, operands + 2);
    actorId = ScriptCmd_ReturnValue(context, actorId);
    parentId = ScriptCmd_ReturnValue(context, parentId);
    ActorSlot_AttachToParentByIndex(actorId, parentId, attachData);
    switch (mode) {
    case 1:
        if (parentId >= 3) {
            ActorRegistry_GetEntityByIndex(parentId)->flags |= 0x10;
        }
        break;
    case 2:
        ActorRegistry_GetEntityByIndex(actorId)->flags |= 8;
        break;
    }
    if (context->scene->actorObjects != NULL) {
        AllocateSlotIfNull(context, actorId);
        SpawnActorModelAt(context->scene->actorObjects[actorId], 0, &data_0205344c, actorId);
        AttachActorToOwner(context->scene->actorObjects[actorId], context->scene->actorObjects[parentId], actorId);
    }
    ActorSlot_SetFlag8ByIndex(actorId, TRUE);
    return 1;
}
