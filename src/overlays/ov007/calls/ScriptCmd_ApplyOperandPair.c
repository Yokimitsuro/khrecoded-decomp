#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *script, ScriptOperand *operand);
extern u32 GetBoundedEntryField(int index);
extern void GrantRewardItem(u32 entry, int *first, int *second);

int ScriptCmd_ApplyOperandPair(void *script, ScriptOperand *operands)
{
    int first = ScriptVm_ReadOperandInt(script, operands);
    int second = ScriptVm_ReadOperandInt(script, operands + 1);

    GrantRewardItem(GetBoundedEntryField(0), &first, &second);
    return 1;
}
