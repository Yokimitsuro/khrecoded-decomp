#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *vm, ScriptOperand *operand);
extern void *func_ov001_0207f060(int groupIndex, int entryIndex);
extern void FieldObject_SetProbeSphere(void *object, BOOL enable, s16 shadowScale, BOOL useVolume);

int ScriptCmd_EnableObjectShadow(void *vm, ScriptOperand *operands)
{
    int groupIndex = ScriptVm_ReadOperandInt(vm, operands);
    int entryIndex = ScriptVm_ReadOperandInt(vm, operands + 1);
    fx32 shadowScale = ScriptVm_ReadOperandFx32(vm, operands + 2);
    int useVolume = ScriptVm_ReadOperandInt(vm, operands + 3);

    FieldObject_SetProbeSphere(func_ov001_0207f060(groupIndex, entryIndex), TRUE, (s16)shadowScale, useVolume);
    return 1;
}
