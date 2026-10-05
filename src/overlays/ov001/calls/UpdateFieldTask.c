#include "nitro/types.h"

typedef struct FieldTask {
    u8 pad_00[0x10];
    s8 matched;
    u8 pad_11;
    s8 kind;
    u8 pad_13;
    s16 id;
} FieldTask;

typedef struct FieldEvent {
    s16 id;
    s8 busy;
} FieldEvent;

extern int func_ov001_02067ed4(void);
extern FieldEvent *func_ov001_0206894c(void);
extern BOOL func_ov001_02069464(FieldTask *task);

int UpdateFieldTask(FieldTask *task)
{
    FieldEvent *event;

    task->matched = 0;
    if (task->kind != func_ov001_02067ed4()) {
        return 0;
    }
    event = func_ov001_0206894c();
    if (event->busy == 0 && (task->id < 0 || task->id == event->id)) {
        task->matched = 1;
    }
    if (func_ov001_02069464(task)) {
        return task->matched;
    }
    return 0;
}
