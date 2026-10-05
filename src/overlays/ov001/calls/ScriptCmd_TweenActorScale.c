#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptContext ScriptContext;

typedef struct ActorModel {
    u8 pad_00[0xb0];
    VecFx32 scale;
} ActorModel;

typedef struct Actor {
    u32 unk_00;
    ActorModel model;
} Actor;

typedef struct PartyEntry {
    u8 pad_000[0x6a0];
    fx32 scale;
} PartyEntry;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(ScriptContext *context, ScriptOperand *operand);
extern Actor *ActorRegistry_GetEntityByIndex(u32 actorId);
extern int EvaluateInterpolationCurve(int curve, u32 duration, int remaining);
extern fx32 ScaleAroundPivot(int t, fx32 target, fx32 start);
extern PartyEntry *func_ov001_0206db5c(int index);

void ScriptCmd_TweenActorScale(ScriptContext *context, ScriptOperand *operands)
{
    int actorId = ScriptVm_ReadOperandInt(context, &operands[0]);
    int duration = ScriptVm_ReadOperandInt(context, &operands[1]);
    fx32 scale = ScriptVm_ReadOperandFx32(context, &operands[2]);
    int curve = ScriptVm_ReadOperandInt(context, &operands[3]);
    Actor *actor = ActorRegistry_GetEntityByIndex((u16)actorId);
    ActorModel *model = &actor->model;

    if (operands[4].value > 0) {
        operands[4].value--;
        if (curve == 2) {
            scale = (scale - operands[5].value) / duration + model->scale.x;
        } else {
            scale = ScaleAroundPivot(EvaluateInterpolationCurve(curve, duration, operands[4].value),
                                              scale, operands[5].value);
        }
    }
    model->scale.z = scale;
    model->scale.y = model->scale.z;
    model->scale.x = model->scale.y;
    if (actorId < 3) {
        func_ov001_0206db5c(actorId)->scale = scale;
    }
}
