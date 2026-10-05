#include "nitro/types.h"

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

typedef struct SecondarySlot {
    s32 first;
    s32 second;
} SecondarySlot;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern void ActorObject_ResetSecondarySlots(void *actor);
extern void ActorObject_SetSecondarySlot(void *actor, const void *src, int index);

int ScriptCmd_SetActorSecondarySlot(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    int slotIndex;
    SecondarySlot slot;

    actorId = ScriptVm_ReadOperandInt(context, operands);
    actorId = ScriptCmd_ReturnValue(context, actorId);
    if (operands[1].type == 0) {
        ActorObject_ResetSecondarySlots(context->scene->actorObjects[actorId]);
    } else {
        slotIndex = ScriptVm_ReadOperandInt(context, &operands[1]);
        slot.first = ScriptVm_ReadOperandInt(context, &operands[2]);
        slot.second = ScriptVm_ReadOperandInt(context, &operands[3]);
        ActorObject_SetSecondarySlot(context->scene->actorObjects[actorId], &slot, slotIndex);
    }
    return 1;
}
