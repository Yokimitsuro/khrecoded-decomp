#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *vm, ScriptOperand *operand);
extern void *FindKind4FieldObject(void);
extern u32 func_ov017_020a4254(void *manager);
extern void *func_ov001_02086384(void *table, int entryIndex);
extern void *AppendPool1Entry(void *manager, VecFx32 *position, u32 managerValue, fx32 speed, int duration);
extern void FormatAndQueueMessage(void *obj, const char *format, u32 flags, void *args);

int ScriptCmd_QueueEntryPositionMessage(void *vm, ScriptOperand *operands)
{
    void *manager = FindKind4FieldObject();
    int entryIndex = ScriptVm_ReadOperandInt(vm, operands);
    BOOL enable = ScriptVm_ReadOperandInt(vm, operands + 1) != 0;
    VecFx32 position;
    u32 managerValue;
    fx32 speed;
    int duration;
    void *entry;

    position.x = ScriptVm_ReadOperandFx32(vm, operands + 2);
    position.y = ScriptVm_ReadOperandFx32(vm, operands + 3);
    position.z = 0;
    managerValue = func_ov017_020a4254(manager);
    speed = ScriptVm_ReadOperandFx32(vm, operands + 4);
    duration = ScriptVm_ReadOperandInt(vm, operands + 5);
    entry = func_ov001_02086384(manager, entryIndex);

    FormatAndQueueMessage(entry, (const char *)1, enable, AppendPool1Entry(manager, &position, managerValue, speed, duration));
    return 1;
}
