#include "nitro/types.h"

typedef struct CallbackTask CallbackTask;

typedef struct CallbackTask {
    u8 pad_00[0x8];
    void *work;
    u8 pad_0C[0x5C];
    void (*onFinish)(CallbackTask *task);
} CallbackTask;

extern void func_ov001_020822d4(void *work);
extern void func_ov001_0207f234(CallbackTask *task, int arg);

void ReleaseTaskWithCallback(CallbackTask *task, int arg)
{
    if (task->onFinish != NULL) {
        task->onFinish(task);
    }
    func_ov001_020822d4(task->work);
    func_ov001_0207f234(task, arg);
}
