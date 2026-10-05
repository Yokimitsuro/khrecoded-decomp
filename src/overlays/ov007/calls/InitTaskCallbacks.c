#include "nitro/types.h"

typedef struct {
    u32 kind;
    u32 priority;
    u32 slot;
    void *data;
} TaskParams;

typedef struct {
    void (*update)(void *task);
    void *unk_04;
    void (*draw)(void *task);
    void *data;
    u8 pad_10[2];
    u8 kind;
    u8 pad_13;
    u8 priority;
    u8 pad_15;
    u16 slot;
} TaskCallbacks;

extern void func_ov007_020a1ba0(void *task);
extern void func_ov007_020a1be0(void *task);

void InitTaskCallbacks(TaskCallbacks *task, const TaskParams *params) {
    task->priority = params->priority;
    task->slot = params->slot;
    task->kind = params->kind;
    task->data = params->data;
    task->update = func_ov007_020a1ba0;
    task->unk_04 = NULL;
    task->draw = func_ov007_020a1be0;
}
