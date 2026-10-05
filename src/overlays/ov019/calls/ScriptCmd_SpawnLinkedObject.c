#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *vm, ScriptOperand *operand);
extern void *func_ov001_0208723c(int tableIndex);
extern u8 func_ov019_020a3348(void *owner, u16 kind, int tag, u16 linkId, u8 linkSlot,
                                     const VecFx32 *position, s8 sizeX, s8 sizeY, s16 rotX, s16 rotY, s16 rotZ,
                                     s8 unused, s8 linkIndex, u32 options);

int ScriptCmd_SpawnLinkedObject(void *vm, ScriptOperand *operands)
{
    int tableIndex = ScriptVm_ReadOperandInt(vm, operands);
    int kind = ScriptVm_ReadOperandInt(vm, operands + 1);
    int tag = ScriptVm_ReadOperandInt(vm, operands + 2);
    u16 linkId;
    u8 linkSlot;
    VecFx32 position;
    int sizeX;
    int sizeY;
    int rotX;
    int rotY;
    int rotZ;
    int unused;
    int linkIndex;
    int options;

    if (operands[3].type == 0) {
        linkId = 0xffff;
        linkSlot = 0xff;
    } else {
        linkId = operands[3].value;
        linkSlot = (u16)((u32)operands[3].value >> 16);
    }
    position.x = ScriptVm_ReadOperandFx32(vm, operands + 4);
    position.y = ScriptVm_ReadOperandFx32(vm, operands + 5);
    position.z = ScriptVm_ReadOperandFx32(vm, operands + 6);
    sizeX = ScriptVm_ReadOperandInt(vm, operands + 7);
    sizeY = ScriptVm_ReadOperandInt(vm, operands + 8);
    rotX = ScriptVm_ReadOperandInt(vm, operands + 9);
    rotY = ScriptVm_ReadOperandInt(vm, operands + 10);
    rotZ = ScriptVm_ReadOperandInt(vm, operands + 11);
    unused = ScriptVm_ReadOperandInt(vm, operands + 12);
    linkIndex = ScriptVm_ReadOperandInt(vm, operands + 13);
    options = ScriptVm_ReadOperandInt(vm, operands + 14);

    func_ov019_020a3348(func_ov001_0208723c(tableIndex), kind, tag, linkId, linkSlot, &position, sizeX,
                               sizeY, rotX, rotY, rotZ, unused, linkIndex, options);
    return 1;
}
