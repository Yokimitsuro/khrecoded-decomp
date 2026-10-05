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
extern void SetScreenFlag200(int enable);
extern void func_ov001_0206a72c(int mode);
extern void BeginScreenFadeOut(int mode);

int ScriptCmd_StartScreenFade(ScriptContext *context, ScriptOperand *operands)
{
    int direction;

    direction = ScriptVm_ReadOperandInt(context, operands);
    if (context->isSkipping != 0) {
        return 1;
    }
    SetScreenFlag200(1);
    switch (direction) {
    case 0:
        func_ov001_0206a72c(0);
        break;
    case 1:
        BeginScreenFadeOut(0);
        break;
    }
    return 0;
}
