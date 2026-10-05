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
extern void *func_ov001_02086384(void *table, int entryIndex);
extern void AppendPool1Batch(void *manager, int count, VecFx32 *points, int mode, fx32 speed, u16 *outIndices);
extern void FormatAndQueueMessage(void *obj, const char *format, u32 flags, void *args);

int ScriptCmd_QueueEntryPathMessages(void *vm, ScriptOperand *operands)
{
    VecFx32 points[256];
    u16 indices[256];
    int mode;
    int entryIndex;
    fx32 speed;
    BOOL enable;
    int count;
    int i;
    void *manager;
    void *entry;

    entryIndex = ScriptVm_ReadOperandInt(vm, operands);
    enable = ScriptVm_ReadOperandInt(vm, operands + 1) ? TRUE : FALSE;
    mode = ScriptVm_ReadOperandInt(vm, operands + 2);
    speed = ScriptVm_ReadOperandFx32(vm, operands + 3);
    operands += 4;
    count = ScriptVm_ReadOperandInt(vm, operands++);
    for (i = 0; i < count; i++) {
        points[i].x = ScriptVm_ReadOperandFx32(vm, operands++);
        points[i].y = ScriptVm_ReadOperandFx32(vm, operands++);
        points[i].z = 0;
    }
    manager = FindKind4FieldObject();
    entry = func_ov001_02086384(manager, entryIndex);
    AppendPool1Batch(manager, count, points, mode, speed, indices);
    for (i = 0; i < count; i++) {
        FormatAndQueueMessage(entry, (const char *)1, enable, (void *)indices[i]);
    }
    return 1;
}
