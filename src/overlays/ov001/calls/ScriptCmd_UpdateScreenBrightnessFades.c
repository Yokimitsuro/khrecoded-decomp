#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptContext ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern int ScriptCmd_UpdateBrightnessFade(ScriptContext *context, ScriptOperand *operands, int screen);

int ScriptCmd_UpdateScreenBrightnessFades(ScriptContext *context, ScriptOperand *operands)
{
    int screen;

    if (operands[2].type == 0) {
        screen = 2;
    } else {
        screen = ScriptVm_ReadOperandInt(context, &operands[2]);
    }
    if (screen == 2) {
        ScriptCmd_UpdateBrightnessFade(context, operands, 0);
        return ScriptCmd_UpdateBrightnessFade(context, operands, 1);
    }
    return ScriptCmd_UpdateBrightnessFade(context, operands, screen);
}
