#include "nitro/types.h"

typedef struct TaskHost {
    u8 pad_00[0x3c];
    u8 task[0x10];
    void *activeList;
    u8 pad_50[0x1bf];
    u8 suspended : 1;
    u8 suspendPending : 1;
} TaskHost;

extern TaskHost *data_ov001_020a0484;
extern void ActorSlot_LinkAsRoot(void *task);

void ResumeTaskAndClearFlags(void) {
    if (data_ov001_020a0484->activeList != NULL) {
        ActorSlot_LinkAsRoot(data_ov001_020a0484->task);
    }
    data_ov001_020a0484->suspended = 0;
    data_ov001_020a0484->suspendPending = 0;
}
