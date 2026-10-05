#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *vm, ScriptOperand *operand);
extern void *func_ov001_0208723c(int group);
extern void CreateKind6FieldObject(void *manager, u16 objectId, int slot, u16 packedLow, u8 packedHigh, VecFx32 *position,
                                s8 linkIndex, s8 linkGroup, fx32 speed);

int ScriptCmd_CreateGroupObject(void *vm, ScriptOperand *operands)
{
    int group = ScriptVm_ReadOperandInt(vm, operands);
    int objectId = ScriptVm_ReadOperandInt(vm, operands + 1);
    int slot = ScriptVm_ReadOperandInt(vm, operands + 2);
    u32 packed = operands[3].value;
    VecFx32 position;
    fx32 speed;
    int linkIndex;
    int linkGroup;

    position.x = ScriptVm_ReadOperandFx32(vm, operands + 4);
    position.y = ScriptVm_ReadOperandFx32(vm, operands + 5);
    position.z = ScriptVm_ReadOperandFx32(vm, operands + 6);
    speed = ScriptVm_ReadOperandFx32(vm, operands + 7);
    linkIndex = ScriptVm_ReadOperandInt(vm, operands + 8);
    linkGroup = ScriptVm_ReadOperandInt(vm, operands + 9);

    CreateKind6FieldObject(func_ov001_0208723c(group), objectId, slot, packed, (u16)(packed >> 16), &position,
                        linkIndex, linkGroup, speed);
    return 1;
}
