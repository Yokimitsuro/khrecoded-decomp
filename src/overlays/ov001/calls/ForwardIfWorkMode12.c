#include "nitro/types.h"

typedef struct FieldWork {
    u8 pad_00[0x7D];
    u8 mode;
} FieldWork;

typedef struct FieldTask {
    u8 pad_00[0x8];
    FieldWork *work;
} FieldTask;

extern int GetAttachPointOffset(FieldTask *task, int arg1, int arg2);

int ForwardIfWorkMode12(FieldTask *task, int arg1, int arg2)
{
    if (task->work->mode == 12) {
        return GetAttachPointOffset(task, arg1, arg2);
    }
    return 0;
}
