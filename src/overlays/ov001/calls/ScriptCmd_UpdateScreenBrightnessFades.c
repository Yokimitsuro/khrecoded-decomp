#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptContext ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern int func_ov001_0208d134(ScriptContext *context, ScriptOperand *operands, int screen);

int ScriptCmd_UpdateScreenBrightnessFades(ScriptContext *context, ScriptOperand *operands)
{
    int screen;

    if (operands[2].type == 0) {
        screen = 2;
    } else {
        screen = ScriptVm_ReadOperandInt(context, &operands[2]);
    }
    if (screen == 2) {
        func_ov001_0208d134(context, operands, 0);
        return func_ov001_0208d134(context, operands, 1);
    }
    return func_ov001_0208d134(context, operands, screen);
}
