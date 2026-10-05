#include "nitro/types.h"

extern int ScriptVm_ReadOperandInt(void *vm, void *cmd);
extern int func_ov001_0207f060(int slot, int elementIndex);
extern void func_ov009_020a0c3c(int element, BOOL enable);

int ScriptCmd_SetObjectElementState(void *vm, void *cmd)
{
    int slot;
    int elementIndex;
    BOOL enable;

    slot = ScriptVm_ReadOperandInt(vm, cmd);
    elementIndex = ScriptVm_ReadOperandInt(vm, (u8 *)cmd + 8);
    enable = ScriptVm_ReadOperandInt(vm, (u8 *)cmd + 0x10) != 0;
    func_ov009_020a0c3c(func_ov001_0207f060(slot, elementIndex), enable);
    return 1;
}
