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
extern int ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern void ActorObject_SetFlagBit4(void *actor, int enable);

int ScriptCmd_SetActorFlagBit4(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    int enable;

    actorId = ScriptVm_ReadOperandInt(context, operands);
    enable = ScriptVm_ReadOperandInt(context, operands + 1) != 0;
    actorId = ScriptCmd_ReturnValue(context, actorId);
    ActorObject_SetFlagBit4(context->scene->actorObjects[actorId], enable);
    return 1;
}
