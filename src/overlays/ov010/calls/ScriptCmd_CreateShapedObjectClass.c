#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 type;
    u32 value;
} ScriptOperand;

typedef struct ShapedClassParams {
    int value;
    s16 kind;
    s8 blendIndex;
    s8 shapeKind;
    VecFx32 size;
} ShapedClassParams;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *vm, ScriptOperand *operand);
extern void *func_ov010_020a08a4(u16 height, const ShapedClassParams *params);
extern void func_ov001_0207ee2c(int slot, void *objectClass);

int ScriptCmd_CreateShapedObjectClass(void *vm, ScriptOperand *operands)
{
    int slot;
    int height;
    ShapedClassParams params;

    slot = ScriptVm_ReadOperandInt(vm, &operands[0]);
    height = ScriptVm_ReadOperandInt(vm, &operands[1]);
    params.kind = ScriptVm_ReadOperandInt(vm, &operands[2]);
    params.blendIndex = ScriptVm_ReadOperandInt(vm, &operands[3]);
    params.value = ScriptVm_ReadOperandInt(vm, &operands[4]);
    params.shapeKind = ScriptVm_ReadOperandInt(vm, &operands[5]);
    params.size.x = ScriptVm_ReadOperandFx32(vm, &operands[6]);
    params.size.y = ScriptVm_ReadOperandFx32(vm, &operands[7]);
    params.size.z = ScriptVm_ReadOperandFx32(vm, &operands[8]);
    func_ov001_0207ee2c(slot, func_ov010_020a08a4((u16)height, &params));
    return 1;
}
