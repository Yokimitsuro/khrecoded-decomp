#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptSceneData {
    u8 pad_00[0x4c];
    void **actorObjects;
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
} ScriptContext;

typedef struct ExtraSlot {
    fx32 rate;
    s32 first;
    s32 second;
} ExtraSlot;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern void ActorObject_ClearExtraSlot(void *actor, int index);
extern void ActorObject_SetExtraSlot(void *actor, const void *src, int index);

int ScriptCmd_SetActorExtraSlot(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    int slotIndex;
    fx32 rate;
    ExtraSlot slot;

    actorId = ScriptVm_ReadOperandInt(context, &operands[0]);
    slotIndex = ScriptVm_ReadOperandInt(context, &operands[1]);
    rate = ScriptVm_ReadOperandFx32(context, &operands[2]);
    actorId = ScriptCmd_ReturnValue(context, actorId);
    if (rate == 0) {
        ActorObject_ClearExtraSlot(context->scene->actorObjects[actorId], slotIndex);
    } else {
        slot.rate = rate;
        slot.first = ScriptVm_ReadOperandInt(context, &operands[3]);
        slot.second = ScriptVm_ReadOperandInt(context, &operands[4]);
        ActorObject_SetExtraSlot(context->scene->actorObjects[actorId], &slot, slotIndex);
    }
    return 1;
}
