#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct QueuedCommand {
    u8 pad_00[4];
    u32 param : 8;
    u32 kind : 8;
    u32 target : 8;
    u32 active : 1;
    u32 unk_04_25 : 7;
    fx32 value;
    u8 pad_0C[8];
} QueuedCommand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *vm, ScriptOperand *operand);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void *FindKind4FieldObject(void);
extern void *func_ov001_02086384(void *table, int entryIndex);
extern void DispatchKind4Entry(void *entry, QueuedCommand *command);

int ScriptCmd_QueueEntryCommand(void *vm, ScriptOperand *operands)
{
    int entryIndex = ScriptVm_ReadOperandInt(vm, operands);
    int target = ScriptVm_ReadOperandInt(vm, operands + 1);
    int param = ScriptVm_ReadOperandInt(vm, operands + 2);
    int kind = ScriptVm_ReadOperandInt(vm, operands + 3);
    fx32 value = ScriptVm_ReadOperandFx32(vm, operands + 4);
    QueuedCommand *command = NNSi_FndAllocFromDefaultHeap(sizeof(QueuedCommand));

    command->param = param;
    command->kind = kind;
    command->target = target;
    command->active = 1;
    command->value = 0;
    if (kind == 3) {
        command->value = value;
    }
    DispatchKind4Entry(func_ov001_02086384(FindKind4FieldObject(), entryIndex), command);
    return 1;
}
