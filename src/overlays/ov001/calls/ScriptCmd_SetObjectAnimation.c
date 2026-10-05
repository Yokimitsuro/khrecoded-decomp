#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    u8 payload[6];
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern void *func_ov001_0207f060(int groupIndex, int entryIndex);
extern void SetObjectAnimTrack(void *object, int animationIndex);

int ScriptCmd_SetObjectAnimation(void *vm, ScriptOperand *operands)
{
    int groupIndex = ScriptVm_ReadOperandInt(vm, operands);
    int entryIndex = ScriptVm_ReadOperandInt(vm, operands + 1);
    int animationIndex = ScriptVm_ReadOperandInt(vm, operands + 2);

    SetObjectAnimTrack(func_ov001_0207f060(groupIndex, entryIndex), animationIndex);
    return 1;
}
