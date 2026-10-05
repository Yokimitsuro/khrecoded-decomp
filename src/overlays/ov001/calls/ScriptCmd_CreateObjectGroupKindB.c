#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern void *func_ov001_02082608(u16 entryCount);
extern void func_ov001_0207ee2c(int groupIndex, void *group);

int ScriptCmd_CreateObjectGroupKindB(void *vm, ScriptOperand *operands)
{
    int groupIndex = ScriptVm_ReadOperandInt(vm, operands);
    int entryCount = ScriptVm_ReadOperandInt(vm, operands + 1);

    func_ov001_0207ee2c(groupIndex, func_ov001_02082608(entryCount));
    return 1;
}
