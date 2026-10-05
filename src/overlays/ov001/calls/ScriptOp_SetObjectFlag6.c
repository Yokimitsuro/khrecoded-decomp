#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    u8 data[8];
} ScriptOperand;

typedef struct FieldObject {
    u8 pad_00[0x4e];
    u16 flags;
} FieldObject;

extern int ScriptVm_ReadOperandInt(void *vm, void *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *vm, void *operand);
extern FieldObject *func_ov001_0207f060(u32 group, u32 index);

int ScriptOp_SetObjectFlag6(void *vm, ScriptOperand *operands)
{
    int group = ScriptVm_ReadOperandInt(vm, &operands[0]);
    int index = ScriptVm_ReadOperandInt(vm, &operands[1]);
    fx32 enable = ScriptVm_ReadOperandFx32(vm, &operands[2]);
    FieldObject *object = func_ov001_0207f060(group, index);

    if (enable != 0) {
        object->flags |= 0x40;
    } else {
        object->flags &= 0xffbf;
    }
    return 1;
}
