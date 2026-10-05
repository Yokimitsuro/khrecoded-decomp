#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x20c];
    void **handles;
} StageManager;

extern StageManager *data_ov001_020a0528;

void *GetStageObjectHandle(u32 id)
{
    u32 index = (id - 1) & 0xffff;
    void *handle;

    if (data_ov001_020a0528 == 0) {
        return 0;
    }
    handle = data_ov001_020a0528->handles[index];
    if (handle == 0) {
        return 0;
    }
    return handle;
}
