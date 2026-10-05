#include "nitro/types.h"

extern int ScriptVm_ReadOperandInt(void *vm, void *operand);
extern void CreateFieldTaskNode(int eventId, BOOL enable, int mode, int *params);

BOOL ScriptCmd_ConfigureEventSlot(void *vm, u8 *operands)
{
    int enable = ScriptVm_ReadOperandInt(vm, operands);
    int eventId = ScriptVm_ReadOperandInt(vm, operands + 8);
    int params[5];

    params[0] = ScriptVm_ReadOperandInt(vm, operands + 0x10);
    params[1] = ScriptVm_ReadOperandInt(vm, operands + 0x18);
    params[2] = ScriptVm_ReadOperandInt(vm, operands + 0x20);
    params[3] = ScriptVm_ReadOperandInt(vm, operands + 0x28);
    params[4] = ScriptVm_ReadOperandInt(vm, operands + 0x30);
    CreateFieldTaskNode(eventId, enable != 0, 7, params);
    return TRUE;
}
