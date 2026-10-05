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
extern void ResetScreenLayer(int screen, BOOL useWhiteClearColor);

int ScriptCmd_ResetScreenLayer(ScriptContext *context, ScriptOperand *operands)
{
    int screen = ScriptVm_ReadOperandInt(context, &operands[0]);
    int useWhiteClearColor = ScriptVm_ReadOperandInt(context, &operands[1]);

    if (context->isSkipping != 0) {
        return 1;
    }
    ResetScreenLayer(screen, useWhiteClearColor);
    return 1;
}
