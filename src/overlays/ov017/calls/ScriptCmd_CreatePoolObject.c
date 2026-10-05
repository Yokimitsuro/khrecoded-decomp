#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *vm, ScriptOperand *operand);
extern void *func_ov001_0208723c(int poolIndex);
extern void SpawnKind7Entry(void *pool, u16 objectId, int slot, u16 packedLow, u8 packedHigh, VecFx32 *position,
                                s8 linkIndex, s8 linkGroup, s16 eventId, s16 mode, s16 modeParam, s8 variant, fx32 speed,
                                BOOL visible);

int ScriptCmd_CreatePoolObject(void *vm, ScriptOperand *operands)
{
    VecFx32 position;
    int poolIndex = ScriptVm_ReadOperandInt(vm, operands);
    int objectId = ScriptVm_ReadOperandInt(vm, operands + 1);
    int slot = ScriptVm_ReadOperandInt(vm, operands + 2);
    u32 packed = operands[3].value;
    fx32 speed;
    int linkIndex;
    int linkGroup;
    int eventId;
    int mode;
    int modeParam;
    int variant;
    int visible;

    position.x = ScriptVm_ReadOperandFx32(vm, operands + 4);
    position.y = ScriptVm_ReadOperandFx32(vm, operands + 5);
    position.z = ScriptVm_ReadOperandFx32(vm, operands + 6);
    speed = ScriptVm_ReadOperandFx32(vm, operands + 7);
    linkIndex = ScriptVm_ReadOperandInt(vm, operands + 8);
    linkGroup = ScriptVm_ReadOperandInt(vm, operands + 9);
    eventId = ScriptVm_ReadOperandInt(vm, operands + 10);
    mode = ScriptVm_ReadOperandInt(vm, operands + 11);
    modeParam = ScriptVm_ReadOperandInt(vm, operands + 12);
    variant = ScriptVm_ReadOperandInt(vm, operands + 13);
    visible = ScriptVm_ReadOperandInt(vm, operands + 14);

    SpawnKind7Entry(func_ov001_0208723c(poolIndex), objectId, slot, packed, (u16)(packed >> 16), &position,
                        linkIndex, linkGroup, eventId, mode, modeParam, variant, speed, visible != 0);
    return 1;
}
