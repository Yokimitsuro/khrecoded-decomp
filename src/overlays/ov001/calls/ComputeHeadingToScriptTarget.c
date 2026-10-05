#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ActorNode {
    u8 pad_00[0xa8];
    VecFx32 position;
} ActorNode;

typedef struct ScriptContext ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern int ByteCode_ResolveOperand(ScriptContext *context, ScriptOperand *operand);
extern ActorNode *ActorRegistry_GetEntityByIndex(u16 actorId);
extern int ProjectRecordPositionDownward(int location, VecFx32 *out);
extern u16 FX_Atan2Idx(int vertical, int horizontal);

u32 ComputeHeadingToScriptTarget(ScriptContext *context, ScriptOperand *target, int actorId)
{
    VecFx32 delta;
    VecFx32 targetPos;

    if (target->type == 1) {
        targetPos = ActorRegistry_GetEntityByIndex(ScriptCmd_ReturnValue(context, ScriptVm_ReadOperandInt(context, target)))->position;
    } else if (target->type == 2) {
        ProjectRecordPositionDownward(ByteCode_ResolveOperand(context, target), &targetPos);
    } else {
        return 1;
    }
    delta = ActorRegistry_GetEntityByIndex(actorId)->position;
    delta.x = targetPos.x - delta.x;
    delta.z = targetPos.z - delta.z;
    return (u16)(0x13fff - FX_Atan2Idx(delta.z, delta.x));
}
