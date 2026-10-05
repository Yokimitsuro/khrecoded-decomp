#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

typedef struct ActorNode {
    u32 flags;
    u16 stateFlags;
    u8 unknown006[0x7a];
    u16 rotation;
    u8 unknown082[0x26];
    VecFx32 position;
} ActorNode;

typedef struct MtxFx43 {
    fx32 m[4][3];
} MtxFx43;

extern int ScriptVm_ReadOperandInt(void *scriptContext, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *scriptContext, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(void *scriptContext, int actorId);
extern VecFx32 *GetSharedCommandDataOffset44(void);
extern ActorNode *ActorRegistry_GetEntityByIndex(u16 actorId);
extern void MTX_Identity43_(MtxFx43 *matrix);
extern void MTX_RotY43_(MtxFx43 *matrix, fx32 sine, fx32 cosine);
extern void MTX_MultVec43(const VecFx32 *vector, const MtxFx43 *matrix, VecFx32 *result);
extern void VEC_Add(const VecFx32 *left, const VecFx32 *right, VecFx32 *result);
extern void ApplyRecordTableEntry5(u16 actorId, int mode, VecFx32 *position);
extern void ActorSlot_SetFlag8ByIndex(u16 actorId, int flag);
extern void ScriptActor_DispatchAndMarkFlag(void *scriptContext, int mode, VecFx32 *position, int actorId);
extern s16 data_02053580[];

int PlaceActorRelativeToActor(void *scriptContext, ScriptOperand *operands) {
    int actorId;
    int referenceId;
    fx32 height;
    VecFx32 orientation;
    VecFx32 position;
    MtxFx43 matrix;
    VecFx32 offset;
    ActorNode *node;
    u16 heading;
    int angle;
    fx32 depth;

    actorId = ScriptVm_ReadOperandInt(scriptContext, operands);
    referenceId = ScriptVm_ReadOperandInt(scriptContext, operands + 1);
    height = ScriptVm_ReadOperandFx32(scriptContext, operands + 2);
    actorId = ScriptCmd_ReturnValue(scriptContext, actorId);
    orientation = *GetSharedCommandDataOffset44();
    position = ActorRegistry_GetEntityByIndex(referenceId)->position;
    depth = operands[3].type == 0 ? height : ScriptVm_ReadOperandFx32(scriptContext, operands + 3);
    offset.x = 0;
    offset.y = height;
    offset.z = depth;
    MTX_Identity43_(&matrix);
    heading = orientation.x;
    angle = heading >> 4;
    MTX_RotY43_(&matrix, data_02053580[angle], data_02053580[(0x400 - angle) & 0xfff]);
    MTX_MultVec43(&offset, &matrix, &offset);
    offset.x = -offset.x;
    VEC_Add(&position, &offset, &position);
    ApplyRecordTableEntry5(actorId, 0, &position);
    node = ActorRegistry_GetEntityByIndex(actorId);
    if ((node->flags & 0x20) == 0) {
        node->rotation = heading;
        node->stateFlags |= 0x20;
    }
    ActorSlot_SetFlag8ByIndex(actorId, 1);
    ScriptActor_DispatchAndMarkFlag(scriptContext, 0, &position, actorId);
    return 1;
}
