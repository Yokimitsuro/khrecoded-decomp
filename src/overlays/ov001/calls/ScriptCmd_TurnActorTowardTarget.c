#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
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
extern ScriptOperand *ScriptVm_ResolveOperand(ScriptContext *context, ScriptOperand *operand);
extern char *ByteCode_ResolveOperand(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern int ComputeHeadingToScriptTarget(ScriptContext *context, ScriptOperand *target, int actorId);
extern void func_ov001_0208a764(void *actorObject, int heading, char *turnAnimation, char *followAnimation);

int ScriptCmd_TurnActorTowardTarget(ScriptContext *context, ScriptOperand *operands)
{
    int actorId = ScriptVm_ReadOperandInt(context, operands);
    ScriptOperand *target = ScriptVm_ResolveOperand(context, operands + 1);
    char *turnAnimation = ByteCode_ResolveOperand(context, operands + 2);
    char *followAnimation = ByteCode_ResolveOperand(context, operands + 3);
    int heading;

    actorId = ScriptCmd_ReturnValue(context, actorId);
    heading = ComputeHeadingToScriptTarget(context, target, actorId);
    func_ov001_0208a764(context->scene->actorObjects[actorId], heading, turnAnimation, followAnimation);
    return 1;
}
