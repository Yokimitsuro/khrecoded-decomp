#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern void *func_ov001_0208724c(int groupIndex, int entryIndex);
extern void CacheEntry_SetActive(void *object, BOOL visible);

int ScriptCmd_SetAuxObjectVisible(void *vm, ScriptOperand *operands)
{
    int groupIndex = ScriptVm_ReadOperandInt(vm, operands);
    int entryIndex = ScriptVm_ReadOperandInt(vm, operands + 1);
    int visible = ScriptVm_ReadOperandInt(vm, operands + 2);

    CacheEntry_SetActive(func_ov001_0208724c(groupIndex, entryIndex), visible != 0);
    return 1;
}
