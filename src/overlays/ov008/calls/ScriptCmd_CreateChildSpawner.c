#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *script, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *script, ScriptOperand *operand);
extern void *func_ov001_0207f050(int classId);
extern void *CreateChildSpawnerObject(void *objectClass, int slotIndex, u16 saveBitOffset, u8 saveBitCount, const VecFx32 *position, int angle);

BOOL ScriptCmd_CreateChildSpawner(void *script, ScriptOperand *operands)
{
    int classId = ScriptVm_ReadOperandInt(script, operands);
    int slotIndex = ScriptVm_ReadOperandInt(script, operands + 1);
    u32 saveBits = operands[2].value;
    VecFx32 position;
    int angle;

    position.x = ScriptVm_ReadOperandFx32(script, operands + 3);
    position.y = ScriptVm_ReadOperandFx32(script, operands + 4);
    position.z = ScriptVm_ReadOperandFx32(script, operands + 5);
    angle = ScriptVm_ReadOperandInt(script, operands + 6);
    CreateChildSpawnerObject(func_ov001_0207f050(classId), slotIndex, saveBits, (u16)(saveBits >> 16), &position, angle);
    return TRUE;
}
