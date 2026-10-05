#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptContext {
    u8 pad_000[0x628];
    s32 isSkipping;
} ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern void ScriptCmd_SetElemField(ScriptContext *context, ScriptOperand *operands);
extern void ScriptCmd_StartScreenBrightnessFade(ScriptContext *context, ScriptOperand *operands, int screen);

int ScriptCmd_BeginBrightnessFade(ScriptContext *context, ScriptOperand *operands)
{
    int screen;

    if (operands[2].type == 0) {
        screen = 2;
    } else {
        screen = ScriptVm_ReadOperandInt(context, &operands[2]);
    }
    if (screen == 2) {
        ScriptCmd_StartScreenBrightnessFade(context, operands, 0);
        ScriptCmd_StartScreenBrightnessFade(context, operands, 1);
    } else {
        ScriptCmd_StartScreenBrightnessFade(context, operands, screen);
    }
    if (ScriptVm_ReadOperandInt(context, &operands[1]) == 0 || context->isSkipping != 0) {
        return 1;
    }
    ScriptCmd_SetElemField(context, operands);
    return 0;
}
