#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

typedef struct ShapeParams {
    s32 kind;
    fx32 extentA;
    fx32 extentB;
    fx32 extentC;
    fx32 extentD;
} ShapeParams;

typedef struct LinkTarget {
    u8 kind;
    u8 group;
    u8 index;
    u8 reserved;
} LinkTarget;

typedef struct ActorEntry {
    u8 pad_00[8];
    u16 flags;
} ActorEntry;

typedef struct Actor {
    u8 pad_000[0xd24];
    ActorEntry entry;
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
extern u32 ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern void AllocateSlotIfNull(ScriptContext *context, int index);
extern void ActorEntry_Init(int slot, ActorEntry *entry, u16 group, const LinkTarget *attributes, const ShapeParams *shape, BOOL flag20, s8 priority);

int ScriptCmd_InitActorCollision(ScriptContext *context, ScriptOperand *operands)
{
    LinkTarget link;
    ShapeParams shape;
    u32 actorId = ScriptCmd_ReturnValue(context, ScriptVm_ReadOperandInt(context, operands));
    fx32 radius = ScriptVm_ReadOperandFx32(context, operands + 1);
    fx32 height = ScriptVm_ReadOperandFx32(context, operands + 2);

    if (height == 0) {
        if (radius == 0) {
            shape.kind = 1;
            shape.extentB = 0x19a;
            shape.extentA = 0x19a;
        } else {
            shape.kind = 2;
            shape.extentB = radius;
        }
    } else {
        shape.kind = 1;
        shape.extentB = radius;
        shape.extentA = height;
    }
    link.kind = 3;
    link.group = actorId;
    AllocateSlotIfNull(context, actorId);
    ActorEntry_Init((u16)actorId, &context->scene->actorObjects[actorId]->entry, 0, &link, &shape, FALSE, 0);
    context->scene->actorObjects[actorId]->entry.flags |= 0x200;
    return 1;
}
