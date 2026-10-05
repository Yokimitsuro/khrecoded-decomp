#include "nitro/types.h"
#include "nitro/fx_types.h"

extern int ScriptVm_ReadOperandInt(void *vm, void *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *vm, void *operand);
extern void *func_ov001_0207f060(int group, int index);
extern void SetTargetPosition_020a1b84(void *mover, const VecFx32 *target);

BOOL ScriptCmd_SetActorTarget(void *vm, u8 *cmd) {
    int group = ScriptVm_ReadOperandInt(vm, cmd);
    int index = ScriptVm_ReadOperandInt(vm, cmd + 8);
    VecFx32 target;

    target.x = ScriptVm_ReadOperandFx32(vm, cmd + 0x10);
    target.y = ScriptVm_ReadOperandFx32(vm, cmd + 0x18);
    target.z = ScriptVm_ReadOperandFx32(vm, cmd + 0x20);
    SetTargetPosition_020a1b84(func_ov001_0207f060(group, index), &target);
    return TRUE;
}
