#include "nitro/types.h"

typedef struct {
    void *owner;
    void *script;
    void *arg;
    u8 pad_0C[0x28];
    void (*update)(void *task);
    u8 pad_38[8];
} ScriptTask;

extern void MI_CpuFill8(void *dest, u8 data, u32 size);
extern void GetIndexedRecordField(void *task);

void InitScriptTask(ScriptTask *task, void *script, void *owner, void *arg) {
    MI_CpuFill8(task, 0, sizeof(ScriptTask));
    task->script = script;
    task->owner = owner;
    task->arg = arg;
    task->update = GetIndexedRecordField;
}
