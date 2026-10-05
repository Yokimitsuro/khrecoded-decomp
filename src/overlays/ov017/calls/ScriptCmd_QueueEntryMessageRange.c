#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern void *FindKind4FieldObject(void);
extern void *func_ov001_02086384(void *table, int entryIndex);
extern void QueueLinkedEntryRange(void *target, void *source, int firstIndex, int lastIndex);

int ScriptCmd_QueueEntryMessageRange(void *vm, ScriptOperand *operands)
{
    int targetIndex = ScriptVm_ReadOperandInt(vm, operands);
    int sourceIndex = ScriptVm_ReadOperandInt(vm, operands + 1);
    int firstIndex = ScriptVm_ReadOperandInt(vm, operands + 2);
    int lastIndex = ScriptVm_ReadOperandInt(vm, operands + 3);
    void *manager = FindKind4FieldObject();
    void *target = func_ov001_02086384(manager, targetIndex);
    void *source = func_ov001_02086384(manager, sourceIndex);

    QueueLinkedEntryRange(target, source, (u16)firstIndex, (u16)lastIndex);
    return 1;
}
