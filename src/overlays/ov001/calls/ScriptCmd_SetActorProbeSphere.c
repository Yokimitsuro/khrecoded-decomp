#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ActorNode {
    u8 pad_00[0x7c];
    void *model;
} ActorNode;

typedef struct ScriptContext ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern ActorNode *ActorRegistry_GetEntityByIndex(u16 actorId);
extern void SetWorldObjectProbeSphere(u16 index, BOOL enable, fx32 radius);
extern void NNS_G3dMdlSetMdlPolygonIDAll(void *model, int polygonId);
extern void ScriptCmd_SetElemField(ScriptContext *context, ScriptOperand *operands);

int ScriptCmd_SetActorProbeSphere(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    int waitFrames;
    fx32 radius;
    ActorNode *node;

    actorId = ScriptVm_ReadOperandInt(context, operands);
    waitFrames = ScriptVm_ReadOperandInt(context, operands + 3);
    radius = ScriptVm_ReadOperandFx32(context, operands + 1);
    actorId = ScriptCmd_ReturnValue(context, actorId);
    if (radius == 0) {
        SetWorldObjectProbeSphere(actorId, FALSE, 0);
    } else {
        node = ActorRegistry_GetEntityByIndex(actorId);
        SetWorldObjectProbeSphere(actorId, TRUE, radius);
        NNS_G3dMdlSetMdlPolygonIDAll(node->model, 0x3f);
    }
    if (waitFrames == 0) {
        return 1;
    }
    operands[0].value = actorId;
    operands[4].value = waitFrames;
    ScriptCmd_SetElemField(context, operands);
    return 0;
}
