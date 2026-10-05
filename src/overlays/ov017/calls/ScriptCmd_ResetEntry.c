#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern void *func_ov001_0208723c(int tableIndex);
extern void *func_ov001_02086384(void *table, int entryIndex);
extern void func_ov017_020a407c(void *entry);

int ScriptCmd_ResetEntry(void *vm, ScriptOperand *operands)
{
    int tableIndex = ScriptVm_ReadOperandInt(vm, operands);
    int entryIndex = ScriptVm_ReadOperandInt(vm, operands + 1);
    void *entry = func_ov001_02086384(func_ov001_0208723c(tableIndex), entryIndex);

    func_ov017_020a407c(entry);
    return 1;
}
