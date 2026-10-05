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
    u16 id;
};

typedef struct FieldTaskParams {
    int kind;
    int id;
    int param;
} FieldTaskParams;

extern void func_ov001_02069cb4(FieldTask *task);
extern void func_ov001_02069d00(FieldTask *task);

void InitFieldTask(FieldTask *task, const FieldTaskParams *params)
{
    task->id = params->id;
    task->kind = params->kind;
    task->param = params->param;
    task->update = func_ov001_02069cb4;
    task->unk_04 = 0;
    task->draw = func_ov001_02069d00;
}
