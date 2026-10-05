#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *vm, ScriptOperand *operand);
extern unsigned int func_ov001_0207f050(int index);
extern void FieldObject_CreateWithTimer(unsigned int group, u16 objectId, u16 param, u8 flags, VecFx32 *position);

BOOL ScriptCmd_AddGroupObjectAtPosition(void *vm, ScriptOperand *operands) {
    VecFx32 position;
    int groupIndex = ScriptVm_ReadOperandInt(vm, &operands[0]);
    int objectId = ScriptVm_ReadOperandInt(vm, &operands[1]);
    u32 packed = operands[2].value;

    position.x = ScriptVm_ReadOperandFx32(vm, &operands[3]);
    position.y = ScriptVm_ReadOperandFx32(vm, &operands[4]);
    position.z = ScriptVm_ReadOperandFx32(vm, &operands[5]);
    FieldObject_CreateWithTimer(func_ov001_0207f050(groupIndex), objectId, packed, (u16)(packed >> 16), &position);
    return TRUE;
}
