#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 type;
    u32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *vm, ScriptOperand *operand);
extern void *func_ov001_0207f050(int index);
extern void *FieldObject_CreateWithShape_020a0958(void *objectClass, int slotIndex, u16 saveBitOffset, u8 saveBitCount, const VecFx32 *position, u16 angle);

int ScriptCmd_CreateObjectWithAngle(void *vm, ScriptOperand *operands)
{
    int classIndex;
    int slotIndex;
    u32 saveBits;
    VecFx32 position;
    int degrees;

    classIndex = ScriptVm_ReadOperandInt(vm, &operands[0]);
    slotIndex = ScriptVm_ReadOperandInt(vm, &operands[1]);
    saveBits = operands[2].value;
    position.x = ScriptVm_ReadOperandFx32(vm, &operands[3]);
    position.y = ScriptVm_ReadOperandFx32(vm, &operands[4]);
    position.z = ScriptVm_ReadOperandFx32(vm, &operands[5]);
    degrees = ScriptVm_ReadOperandInt(vm, &operands[6]);
    FieldObject_CreateWithShape_020a0958(func_ov001_0207f050(classIndex), (u16)slotIndex, (u16)saveBits, (u8)(u16)(saveBits >> 16), &position, (u16)((degrees << 16) / 360));
    return 1;
}
