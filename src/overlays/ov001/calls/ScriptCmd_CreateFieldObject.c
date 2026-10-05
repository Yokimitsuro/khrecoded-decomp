#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    u32 value;
} ScriptOperand;

typedef struct ScriptContext ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(ScriptContext *context, ScriptOperand *operand);
extern void *func_ov001_0207f050(int index);
extern void *func_ov001_020826c4(void *objectClass, u16 slotIndex, u16 saveBitOffset, u8 saveBitCount,
                                                    const VecFx32 *position, u32 typeId, u32 userParam);

BOOL ScriptCmd_CreateFieldObject(ScriptContext *context, ScriptOperand *operands)
{
    VecFx32 position;
    int classIndex = ScriptVm_ReadOperandInt(context, &operands[0]);
    int slotIndex = ScriptVm_ReadOperandInt(context, &operands[1]);
    u32 saveBits = operands[2].value;
    int typeId;
    int userParam;

    position.x = ScriptVm_ReadOperandFx32(context, &operands[3]);
    position.y = ScriptVm_ReadOperandFx32(context, &operands[4]);
    position.z = ScriptVm_ReadOperandFx32(context, &operands[5]);
    typeId = ScriptVm_ReadOperandInt(context, &operands[6]);
    userParam = ScriptVm_ReadOperandInt(context, &operands[7]);
    func_ov001_020826c4(func_ov001_0207f050(classIndex), slotIndex, saveBits & 0xFFFF,
                                          (u16)(saveBits >> 16), &position, typeId, userParam);
    return TRUE;
}
