#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *vm, ScriptOperand *operand);
extern void *func_ov001_02081fd4(u16 entryCount, int resourceId, fx32 width, fx32 depth);
extern void func_ov001_0207ee2c(int groupIndex, void *group);

int ScriptCmd_CreateObjectGroupKindD(void *vm, ScriptOperand *operands)
{
    int groupIndex = ScriptVm_ReadOperandInt(vm, operands);
    int entryCount = ScriptVm_ReadOperandInt(vm, operands + 1);
    int resourceId = ScriptVm_ReadOperandInt(vm, operands + 2);
    fx32 width = ScriptVm_ReadOperandFx32(vm, operands + 3);
    fx32 depth = ScriptVm_ReadOperandFx32(vm, operands + 4);

    func_ov001_0207ee2c(groupIndex, func_ov001_02081fd4(entryCount, resourceId, width, depth));
    return 1;
}
