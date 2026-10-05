#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern const s16 data_02053580[];
extern int ScriptVm_ReadOperandInt(void *script, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *script, ScriptOperand *operand);
extern void *func_ov001_0207f050(int classId);
extern void *CreateDelayedGimmickObject(void *objectClass, u16 slotIndex, u16 saveBitOffset, u8 saveBitCount, const VecFx32 *position, const VecFx32 *openOffset, fx32 duration, int mode);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

BOOL ScriptCmd_CreateDelayedGimmick(void *script, ScriptOperand *operands)
{
    int classId = ScriptVm_ReadOperandInt(script, operands);
    int slotIndex = ScriptVm_ReadOperandInt(script, operands + 1);
    u32 saveBits = operands[2].value;
    VecFx32 position;
    VecFx32 direction;
    fx32 angle;
    fx32 duration;
    int mode;
    int index;

    position.x = ScriptVm_ReadOperandFx32(script, operands + 3);
    position.y = ScriptVm_ReadOperandFx32(script, operands + 4);
    position.z = ScriptVm_ReadOperandFx32(script, operands + 5);
    angle = ScriptVm_ReadOperandFx32(script, operands + 6);
    duration = ScriptVm_ReadOperandFx32(script, operands + 7);
    mode = ScriptVm_ReadOperandFx32(script, operands + 8);
    index = (u16)((((s64)angle << 16) / 0x168000) & 0xffff) >> 4;
    direction = MakeVec(data_02053580[(0x400 - index) & 0xfff], 0, data_02053580[index]);
    CreateDelayedGimmickObject(func_ov001_0207f050(classId), slotIndex, saveBits, (u16)(saveBits >> 16), &position, &direction, duration, mode);
    return TRUE;
}
