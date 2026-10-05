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

extern char data_ov001_020a0250[];
extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern char *ByteCode_ResolveOperand(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(ScriptContext *context, int value);
extern int _s32_div_f(int dividend, int divisor);
extern void func_ov001_0208a764(void *actorObject, int heading, char *turnAnimation, char *followAnimation);

int ScriptCmd_TurnActorToHeading(ScriptContext *context, ScriptOperand *operands)
{
    int actorId;
    int heading;
    char *turnAnimation;
    char *followAnimation;

    actorId = ScriptVm_ReadOperandInt(context, operands);
    heading = ScriptVm_ReadOperandInt(context, operands + 1);
    actorId = ScriptCmd_ReturnValue(context, actorId);
    heading = (u16)_s32_div_f(heading << 16, 360);
    if (operands[2].type == 2 || operands[2].type == 0x40) {
        turnAnimation = ByteCode_ResolveOperand(context, operands + 2);
    } else {
        turnAnimation = data_ov001_020a0250;
    }
    if (operands[3].type == 2 || operands[3].type == 0x40) {
        followAnimation = ByteCode_ResolveOperand(context, operands + 3);
    } else {
        followAnimation = data_ov001_020a0250;
    }
    func_ov001_0208a764(context->scene->actorObjects[actorId], heading, turnAnimation, followAnimation);
    return 1;
}
