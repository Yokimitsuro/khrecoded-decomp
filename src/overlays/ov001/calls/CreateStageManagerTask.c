#include "nitro/types.h"

typedef struct StageManager {
    u8 pad_00[4];
    void *task;
} StageManager;

extern u8 data_ov001_020a0360[];
extern StageManager *data_ov001_020a0528;
extern void *func_0202a45c(void *descriptor, void *userData);

BOOL CreateStageManagerTask(void *userData)
{
    data_ov001_020a0528->task = func_0202a45c(data_ov001_020a0360, userData);
    return TRUE;
}
