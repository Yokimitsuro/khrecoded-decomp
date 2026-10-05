#include "nitro/types.h"

extern int ScriptVm_ReadOperandInt(void *vm, void *operand);
extern u32 func_ov001_0207b348(int mode);
extern u32 func_ov001_0207b3f4(void);
extern void ScriptCmd_SetElemField(void *vm, void *cmd);

BOOL ScriptCmd_WaitMenuState(void *vm, void *cmd)
{
    switch (ScriptVm_ReadOperandInt(vm, cmd)) {
    case 0:
        if (func_ov001_0207b348(0)) {
            return TRUE;
        }
        break;
    case 1:
        if (func_ov001_0207b3f4() == 2 || func_ov001_0207b348(2)) {
            return TRUE;
        }
        break;
    default:
        return TRUE;
    }
    ScriptCmd_SetElemField(vm, cmd);
    return FALSE;
}
