#include "nitro/types.h"

#define OBJECT_KIND_OV018 6

extern int ScriptVm_ReadOperandInt(void *vm, void *cmd);
extern void *func_ov001_02086eb8(int kind, int slot, int id, int arg);
extern void func_ov001_02086fb8(int slot, void *object);

int ScriptCmd_CreateSlotObject(void *vm, void *cmd)
{
    int slot = ScriptVm_ReadOperandInt(vm, cmd);
    int id = ScriptVm_ReadOperandInt(vm, (u8 *)cmd + 8);
    void *object = func_ov001_02086eb8(OBJECT_KIND_OV018, slot, id, 0);

    func_ov001_02086fb8(slot, object);
    return 1;
}
