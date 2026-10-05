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
extern void func_ov036_020bd38c(int entityId, int motionIndex);

int ScriptCmd_SetEntityMotion(ScriptContext *context, ScriptOperand *operands)
{
    int entityId = ScriptVm_ReadOperandInt(context, &operands[0]);
    int motionIndex = ScriptVm_ReadOperandInt(context, &operands[1]);

    if (context->isSkipping != 0) {
        return 1;
    }
    func_ov036_020bd38c(entityId, motionIndex);
    return 1;
}
