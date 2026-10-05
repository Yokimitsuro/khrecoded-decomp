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
extern void SpawnStackedBlock(void *table, u16 objectId, int slot, u16 packedLow, u8 packedHigh, VecFx32 *position,
                                s8 sizeX, s8 sizeY, s16 angleX, s16 angleY, s16 angleZ, s8 mode, fx32 param);

int ScriptCmd_CreatePanelObject(void *vm, ScriptOperand *operands)
{
    int tableIndex = ScriptVm_ReadOperandInt(vm, operands);
    int objectId = ScriptVm_ReadOperandInt(vm, operands + 1);
    int slot = ScriptVm_ReadOperandInt(vm, operands + 2);
    u32 packed = operands[3].value;
    VecFx32 position;
    fx32 param;
    int sizeX;
    int sizeY;
    int angleX;
    int angleY;
    int angleZ;
    int mode;

    position.x = ScriptVm_ReadOperandFx32(vm, operands + 4);
    position.y = ScriptVm_ReadOperandFx32(vm, operands + 5);
    position.z = ScriptVm_ReadOperandFx32(vm, operands + 6);
    param = ScriptVm_ReadOperandFx32(vm, operands + 7);
    sizeX = ScriptVm_ReadOperandInt(vm, operands + 8);
    sizeY = ScriptVm_ReadOperandInt(vm, operands + 9);
    angleX = ScriptVm_ReadOperandInt(vm, operands + 10);
    angleY = ScriptVm_ReadOperandInt(vm, operands + 11);
    angleZ = ScriptVm_ReadOperandInt(vm, operands + 12);
    mode = ScriptVm_ReadOperandInt(vm, operands + 13);

    SpawnStackedBlock(func_ov001_0208723c(tableIndex), objectId, slot, packed, (u16)(packed >> 16), &position,
                        sizeX, sizeY, angleX, angleY, angleZ, mode, param);
    return 1;
}
