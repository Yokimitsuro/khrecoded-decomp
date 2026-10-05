#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad2;
    s32 payload;
} ScriptOperand;

typedef void (*ScriptHandlerFunc)(u16 low, u16 high, s32 value);

typedef struct ScriptObj {
    u8 pad_00[0x644];
    ScriptHandlerFunc handler;
} ScriptObj;

extern ScriptOperand *ScriptVm_ResolveOperand(void *obj, void *cmd);
extern int ScriptVm_ReadOperandInt(void *obj, void *cmd);

int ScriptCmd_CopyOperandOrInvokeHandler(ScriptObj *obj, ScriptOperand *cmd)
{
    ScriptOperand *operand = ScriptVm_ResolveOperand(obj, cmd + 1);

    if (cmd->type == 8) {
        ScriptOperand *target = ScriptVm_ResolveOperand(obj, cmd);
        target->type = operand->type;
        target->pad2 = 0;
        target->payload = operand->payload;
    } else if (cmd->type == 4) {
        int value = ScriptVm_ReadOperandInt(obj, operand);
        u32 packed = (u32)cmd->payload;
        obj->handler((u16)packed, (u16)(packed >> 16), value);
    }

    return 1;
}
