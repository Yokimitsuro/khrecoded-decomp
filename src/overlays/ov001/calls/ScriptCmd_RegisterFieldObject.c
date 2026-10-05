#include "nitro/types.h"

typedef struct FieldObjectSpawn {
    u16 param;
    u8 variant;
} FieldObjectSpawn;

extern int ScriptVm_ReadOperandInt(void *vm, void *operand);
extern void *CreateFieldObjectClassType16(u16 classId, FieldObjectSpawn *spawn);
extern void func_ov001_0207ee2c(int index, void *entry);

BOOL ScriptCmd_RegisterFieldObject(void *vm, u8 *cmd)
{
    int index = ScriptVm_ReadOperandInt(vm, cmd);
    int classId = ScriptVm_ReadOperandInt(vm, cmd + 8);
    FieldObjectSpawn spawn;

    spawn.param = ScriptVm_ReadOperandInt(vm, cmd + 0x10);
    spawn.variant = ScriptVm_ReadOperandInt(vm, cmd + 0x18);
    func_ov001_0207ee2c(index, CreateFieldObjectClassType16(classId, &spawn));
    return TRUE;
}
