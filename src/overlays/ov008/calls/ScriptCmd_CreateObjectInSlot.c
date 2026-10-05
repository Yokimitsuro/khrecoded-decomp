#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *script, ScriptOperand *operand);
extern void *func_ov008_020a1128(u16 objectId);
extern void func_ov001_0207ee2c(int slotIndex, void *object);

int ScriptCmd_CreateObjectInSlot(void *script, ScriptOperand *operands)
{
    int slotIndex = ScriptVm_ReadOperandInt(script, operands);
    int objectId = ScriptVm_ReadOperandInt(script, operands + 1);

    func_ov001_0207ee2c(slotIndex, func_ov008_020a1128((u16)objectId));
    return 1;
}
