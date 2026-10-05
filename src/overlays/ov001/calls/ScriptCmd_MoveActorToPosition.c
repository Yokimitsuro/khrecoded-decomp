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

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(ScriptContext *context, ScriptOperand *operand);
extern char *ByteCode_ResolveOperand(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern void PlanActorJump(void *actor, VecFx32 *destination, char *moveMotion, char *secondaryMotion);

int ScriptCmd_MoveActorToPosition(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    char *moveMotion;
    char *secondaryMotion;
    VecFx32 destination;

    actorId = ScriptVm_ReadOperandInt(context, operands);
    moveMotion = ByteCode_ResolveOperand(context, operands + 3);
    secondaryMotion = ByteCode_ResolveOperand(context, operands + 4);
    actorId = ScriptCmd_ReturnValue(context, actorId);
    destination.x = ScriptVm_ReadOperandFx32(context, operands + 1);
    destination.y = 0;
    destination.z = ScriptVm_ReadOperandFx32(context, operands + 2);
    PlanActorJump(context->scene->actorObjects[actorId], &destination, moveMotion, secondaryMotion);
    return 1;
}
