#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern void *func_ov001_02086eb8(int kind, int slot, int id, int arg);
extern void func_ov001_02086fb8(int slot, void *object);

int ScriptCmd_CreateSlotObjectKind1(void *vm, ScriptOperand *operands)
{
    int slot = ScriptVm_ReadOperandInt(vm, operands);
    int id = ScriptVm_ReadOperandInt(vm, operands + 1);
    void *object = func_ov001_02086eb8(1, slot, id, 0);

    func_ov001_02086fb8(slot, object);
    return 1;
}
