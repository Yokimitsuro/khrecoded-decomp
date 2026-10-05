#include "nitro/types.h"

typedef struct {
    u32 type;
    u32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern void func_ov035_020baf30(u32 count, s16 *values, u8 a, u8 b);

BOOL ScriptCmd_PlayValueSequence(void *vm, ScriptOperand *op) {
    u8 first = ScriptVm_ReadOperandInt(vm, op++);
    u8 second = ScriptVm_ReadOperandInt(vm, op++);
    int count = ScriptVm_ReadOperandInt(vm, op++);
    s16 values[32];
    int i;

    for (i = 0; i < count; i++) {
        values[i] = ScriptVm_ReadOperandInt(vm, op++);
    }
    func_ov035_020baf30(count, values, first, second);
    return TRUE;
}
