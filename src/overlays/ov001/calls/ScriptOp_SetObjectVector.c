#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    u8 data[8];
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, void *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *vm, void *operand);
extern void *func_ov001_0207f060(u32 group, u32 index);
extern void func_ov001_020814dc(void *object, VecFx32 *value);

int ScriptOp_SetObjectVector(void *vm, ScriptOperand *operands)
{
    int group = ScriptVm_ReadOperandInt(vm, &operands[0]);
    int index = ScriptVm_ReadOperandInt(vm, &operands[1]);
    VecFx32 value;

    value.x = ScriptVm_ReadOperandFx32(vm, &operands[2]);
    value.y = ScriptVm_ReadOperandFx32(vm, &operands[3]);
    value.z = ScriptVm_ReadOperandFx32(vm, &operands[4]);
    func_ov001_020814dc(func_ov001_0207f060(group, index), &value);
    return 1;
}
