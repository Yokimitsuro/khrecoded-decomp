#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern void *FindKind4FieldObject(void);
extern void InitPool1(void *manager, s32 capacity);

int ScriptCmd_InitPool1(void *vm, ScriptOperand *operands)
{
    int capacity = ScriptVm_ReadOperandInt(vm, operands);

    InitPool1(FindKind4FieldObject(), (u16)capacity);
    return 1;
}
