#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ActorNode {
    u32 flags;
    u16 dirtyFlags;
    u8 pad_06[0x7a];
    u16 rotationY;
} ActorNode;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern s32 ScriptCmd_ReturnValue(void *context, s32 value);
extern int ScriptVm_ReadOperandFx32(void *context, ScriptOperand *operand);
extern char *ByteCode_ResolveOperand(void *context, ScriptOperand *operand);
extern void ApplyRecordTableEntry5(u16 index, char *name, VecFx32 *position);
extern ActorNode *ActorRegistry_GetEntityByIndex(u16 index);
extern void ActorSlot_SetFlag8ByIndex(u16 index, BOOL enable);
extern void ScriptActor_DispatchAndMarkFlag(void *context, char *name, VecFx32 *position, u32 actorId);

int ScriptCmd_PlaceActor(void *context, ScriptOperand *operands)
{
    u32 actorId;
    VecFx32 position;
    char *name;
    u16 angle;
    ActorNode *actor;

    actorId = ScriptCmd_ReturnValue(context, ScriptVm_ReadOperandInt(context, operands));
    position.x = ScriptVm_ReadOperandFx32(context, operands + 2);
    position.y = ScriptVm_ReadOperandFx32(context, operands + 3);
    position.z = ScriptVm_ReadOperandFx32(context, operands + 4);
    if (operands[1].type == 0) {
        name = NULL;
        angle = (ScriptVm_ReadOperandInt(context, operands + 5) << 16) / 360;
        ApplyRecordTableEntry5(actorId, NULL, &position);
        actor = ActorRegistry_GetEntityByIndex(actorId);
        if (!(actor->flags & 0x20)) {
            actor->rotationY = angle;
            actor->dirtyFlags |= 0x20;
        }
    } else {
        name = ByteCode_ResolveOperand(context, operands + 1);
        ApplyRecordTableEntry5(actorId, name, &position);
    }
    ActorSlot_SetFlag8ByIndex(actorId, TRUE);
    ScriptActor_DispatchAndMarkFlag(context, name, &position, actorId);
    return 1;
}
