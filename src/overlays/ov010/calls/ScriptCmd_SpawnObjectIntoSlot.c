#include "nitro/types.h"

extern int ScriptVm_ReadOperandInt(void *vm, void *cmd);
extern void *func_ov010_020a0bf4(u16 param);
extern void func_ov001_0207ee2c(int slotIndex, void *object);

int ScriptCmd_SpawnObjectIntoSlot(void *vm, void *cmd)
{
    int slotIndex = ScriptVm_ReadOperandInt(vm, cmd);
    int param = ScriptVm_ReadOperandInt(vm, (u8 *)cmd + 8);
    void *object = func_ov010_020a0bf4((u16)param);
    func_ov001_0207ee2c(slotIndex, object);
    return 1;
}
