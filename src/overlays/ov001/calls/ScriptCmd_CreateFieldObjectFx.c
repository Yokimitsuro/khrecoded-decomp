#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    u32 value;
} ScriptOperand;

typedef struct ScriptContext ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(ScriptContext *context, ScriptOperand *operand);
extern void *func_ov001_0207f050(int index);
extern void *func_ov001_02085ca4(void *objectClass, u16 slotIndex, u16 saveBitOffset, u8 saveBitCount, fx32 param,
                                 u16 angle, VecFx32 *position);

BOOL ScriptCmd_CreateFieldObjectFx(ScriptContext *context, ScriptOperand *operands)
{
    VecFx32 position;
    int classIndex = ScriptVm_ReadOperandInt(context, &operands[0]);
    int slotIndex = ScriptVm_ReadOperandInt(context, &operands[1]);
    u32 saveBits = operands[2].value;
    fx32 param = ScriptVm_ReadOperandFx32(context, &operands[3]);
    fx32 degrees = ScriptVm_ReadOperandFx32(context, &operands[4]);

    position.x = ScriptVm_ReadOperandFx32(context, &operands[5]);
    position.y = ScriptVm_ReadOperandFx32(context, &operands[6]);
    position.z = ScriptVm_ReadOperandFx32(context, &operands[7]);
    func_ov001_02085ca4(func_ov001_0207f050(classIndex), slotIndex, saveBits & 0xFFFF, (u16)(saveBits >> 16), param,
                        (((s64)degrees << 16) / (360 * FX32_ONE)) & 0xFFFF, &position);
    return TRUE;
}
