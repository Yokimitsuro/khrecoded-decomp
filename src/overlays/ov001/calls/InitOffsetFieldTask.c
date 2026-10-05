#include "nitro/types.h"

typedef struct FieldTask FieldTask;

struct FieldTask {
    void (*update)(FieldTask *task);
    u32 unk_04;
    void (*draw)(FieldTask *task);
    int param;
    u8 pad_10[2];
    u8 kind;
    u8 pad_13;
    int target;
    s8 offsetX;
    s8 offsetY;
};

typedef struct FieldTaskParams {
    int kind;
    int target;
    s8 offsetX;
    s8 offsetY;
    u8 pad_0a[2];
    int param;
} FieldTaskParams;

extern void EventTrigger_CheckCounterGoal(FieldTask *task);
extern void func_ov001_020698ac(FieldTask *task);

void InitOffsetFieldTask(FieldTask *task, const FieldTaskParams *params)
{
    task->kind = params->kind;
    task->param = params->param;
    task->target = params->target;
    task->offsetX = params->offsetX;
    task->offsetY = params->offsetY;
    task->update = EventTrigger_CheckCounterGoal;
    task->draw = func_ov001_020698ac;
}
