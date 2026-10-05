#include "nitro/types.h"

extern int ScriptVm_ReadOperandInt(void *vm, void *operand);
extern void MarkSessionIntroDone(void);
extern void func_ov001_02064d44(void);

int ScriptCmd_ToggleSessionBit15(void *vm, void *operand) {
    if (ScriptVm_ReadOperandInt(vm, operand) != 0) {
        MarkSessionIntroDone();
    } else {
        func_ov001_02064d44();
    }
    return 1;
}
