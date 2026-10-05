#include "nitro/types.h"

typedef struct ScriptOperand {
    u32 type;
    u32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *op);
extern void PostPendingRequest(u16 requestId, u8 requestArg);
extern void SetupSlotPanelMode(int mode, int enable);

int ScriptCmd_PostRequestAndSetPanel(void *vm, ScriptOperand *op)
{
    int value = ScriptVm_ReadOperandInt(vm, op);
    u16 requestId = op[1].value;
    u8 requestArg = (u16)(op[1].value >> 16);
    if (value != 0) {
        PostPendingRequest(requestId, requestArg);
    }
    SetupSlotPanelMode(2, value);
    return 1;
}
