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
extern fx32 ScriptVm_ReadOperandFx32(ScriptContext *context, ScriptOperand *operand);
extern ScriptOperand *ScriptVm_ResolveOperand(ScriptContext *context, ScriptOperand *operand);
extern int ByteCode_ResolveOperand(ScriptContext *context, ScriptOperand *operand);
extern int _s32_div_f(int dividend, int divisor);
extern ActorNode *ActorRegistry_GetEntityByIndex(u16 actorId);
extern int ProjectRecordPositionDownward(int location, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern const s16 data_02053580[];

void ResolveScriptTargetPosition(ScriptContext *context, ScriptOperand *operands, int actorId, VecFx32 *out)
{
    VecFx32 offset;
    VecFx32 direction;
    fx32 distance;
    ScriptOperand *location;
    int angleIndex;

    distance = ScriptVm_ReadOperandFx32(context, operands + 6);
    location = ScriptVm_ResolveOperand(context, operands + 1);
    offset.x = ScriptVm_ReadOperandFx32(context, operands + 2);
    offset.y = ScriptVm_ReadOperandFx32(context, operands + 3);
    offset.z = ScriptVm_ReadOperandFx32(context, operands + 4);
    switch (location->type) {
    case 2:
        ProjectRecordPositionDownward(ByteCode_ResolveOperand(context, location), out);
        VEC_Add(out, &offset, out);
        break;
    case 1:
        angleIndex = (u16)_s32_div_f(ScriptVm_ReadOperandInt(context, location) << 16, 360) >> 4;
        direction.x = data_02053580[angleIndex];
        direction.y = 0;
        direction.z = data_02053580[(0x400 - angleIndex) & 0xfff];
        VEC_MultAdd(distance, &direction, &ActorRegistry_GetEntityByIndex(actorId)->position, out);
        break;
    case 0:
        *out = offset;
        break;
    }
}
