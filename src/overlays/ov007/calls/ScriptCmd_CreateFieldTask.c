#include "nitro/types.h"

extern int ScriptVm_ReadOperandInt(void *vm, void *operand);
extern void *func_ov001_02069274(int taskId, BOOL enabled, int kind, int *params);

BOOL ScriptCmd_CreateFieldTask(void *vm, u8 *cmd) {
    int enabled = ScriptVm_ReadOperandInt(vm, cmd);
    int taskId = ScriptVm_ReadOperandInt(vm, cmd + 8);
    int params[4];

    params[0] = ScriptVm_ReadOperandInt(vm, cmd + 0x10);
    params[1] = ScriptVm_ReadOperandInt(vm, cmd + 0x18);
    params[2] = ScriptVm_ReadOperandInt(vm, cmd + 0x20);
    params[3] = ScriptVm_ReadOperandInt(vm, cmd + 0x28);
    func_ov001_02069274(taskId, enabled != 0, 9, params);
    return TRUE;
}
