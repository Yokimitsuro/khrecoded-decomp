#include "nitro/types.h"

extern int ScriptVm_ReadOperandInt(void *vm, void *cmd);
extern void *func_ov009_020a0af0(u16 elementCount);
extern void func_ov001_0207ee2c(int slot, void *object);

int ScriptCmd_CreateObjectInSlot_020a0540(void *vm, void *cmd)
{
    int slot;
    u32 elementCount;

    slot = ScriptVm_ReadOperandInt(vm, cmd);
    elementCount = ScriptVm_ReadOperandInt(vm, (u8 *)cmd + 8);
    func_ov001_0207ee2c(slot, func_ov009_020a0af0(elementCount));
    return 1;
}
