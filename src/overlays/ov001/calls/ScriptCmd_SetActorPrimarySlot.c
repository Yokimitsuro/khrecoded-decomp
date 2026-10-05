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

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern int ScriptVm_ReadOperandFx32(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern void ActorObject_SetPrimarySlot(void *actor, u32 handler, u32 arg);

int ScriptCmd_SetActorPrimarySlot(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    u32 arg;
    u32 handler;

    actorId = ScriptVm_ReadOperandInt(context, operands);
    arg = ScriptVm_ReadOperandInt(context, operands + 2);
    handler = ScriptVm_ReadOperandFx32(context, operands + 1);
    actorId = ScriptCmd_ReturnValue(context, actorId);
    ActorObject_SetPrimarySlot(context->scene->actorObjects[actorId], handler, arg);
    return 1;
}
