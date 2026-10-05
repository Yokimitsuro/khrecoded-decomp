#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *vm, ScriptOperand *operand);
extern void *func_ov001_0207f050(int groupIndex);
extern void func_ov001_0207f8f4(void *group, fx32 interactRange);

int ScriptCmd_SetObjectGroupInteractRange(void *vm, ScriptOperand *operands)
{
    int groupIndex = ScriptVm_ReadOperandInt(vm, operands);
    fx32 interactRange = ScriptVm_ReadOperandFx32(vm, operands + 1);

    func_ov001_0207f8f4(func_ov001_0207f050(groupIndex), interactRange);
    return 1;
}
