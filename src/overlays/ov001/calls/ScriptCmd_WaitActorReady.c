#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptSceneData {
    u8 pad_00[0x4c];
    u8 **actorObjects;
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
} ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern BOOL func_ov001_0208a44c(u8 *actor, int mode);

int ScriptCmd_WaitActorReady(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    int mode;

    actorId = ScriptVm_ReadOperandInt(context, operands);
    mode = ScriptVm_ReadOperandInt(context, operands + 1);
    actorId = ScriptCmd_ReturnValue(context, actorId);
    if (func_ov001_0208a44c(context->scene->actorObjects[actorId], mode) != 0) {
        return 1;
    }
    return 0;
}
