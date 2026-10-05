#include "nitro/types.h"

extern int ScriptVm_ReadOperandInt(void *vm, void *cmd);
extern u32 func_ov001_0207f060(u32 slot, u32 elementIndex);
extern void SetFlagBit0x10At0x4e(int element, BOOL enable);

int ScriptCmd_SetObjectElementFlag(void *vm, void *cmd)
{
    u32 slot;
    u32 elementIndex;
    BOOL enable;

    slot = ScriptVm_ReadOperandInt(vm, cmd);
    elementIndex = ScriptVm_ReadOperandInt(vm, (u8 *)cmd + 8);
    enable = ScriptVm_ReadOperandInt(vm, (u8 *)cmd + 0x10);
    SetFlagBit0x10At0x4e(func_ov001_0207f060(slot, elementIndex), enable);
    return 1;
}
