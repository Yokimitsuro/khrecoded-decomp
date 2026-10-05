#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *vm, ScriptOperand *operand);
extern void *func_ov001_0207f060(int groupIndex, int entryIndex);
extern void func_ov001_0207fac0(void *object, fx32 cullRadius);

int ScriptCmd_SetObjectCullRadius(void *vm, ScriptOperand *operands)
{
    int groupIndex = ScriptVm_ReadOperandInt(vm, operands);
    int entryIndex = ScriptVm_ReadOperandInt(vm, operands + 1);
    fx32 cullRadius = ScriptVm_ReadOperandFx32(vm, operands + 2);

    func_ov001_0207fac0(func_ov001_0207f060(groupIndex, entryIndex), cullRadius);
    return 1;
}
