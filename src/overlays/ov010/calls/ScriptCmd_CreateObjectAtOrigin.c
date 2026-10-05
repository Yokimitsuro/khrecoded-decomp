#include "nitro/types.h"

typedef struct {
    u32 type;
    u32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern void *func_ov001_0207f050(int index);
extern void *FieldObject_CreateAtOrigin(void *objectClass, int slotIndex, u16 saveBitOffset, u8 saveBitCount);

int ScriptCmd_CreateObjectAtOrigin(void *vm, ScriptOperand *operands)
{
    int classIndex;
    int slotIndex;
    u32 saveBits;

    classIndex = ScriptVm_ReadOperandInt(vm, &operands[0]);
    slotIndex = ScriptVm_ReadOperandInt(vm, &operands[1]);
    saveBits = operands[2].value;
    FieldObject_CreateAtOrigin(func_ov001_0207f050(classIndex), (u16)slotIndex, (u16)saveBits, (u8)(u16)(saveBits >> 16));
    return 1;
}
