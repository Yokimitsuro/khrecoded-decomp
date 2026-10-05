#include "nitro/types.h"

typedef struct {
    u8 data[0x3c8];
} StageActor;

typedef struct {
    u8 pad_00[0x4b14];
    StageActor actors[64];
} StageManager;

extern StageManager *data_ov001_020a0528;

StageActor *GetStageActor(int id)
{
    int index = id - 1;

    if (data_ov001_020a0528 == 0) {
        return 0;
    }
    if (index < 0) {
        return 0;
    }
    if (index < 64) {
        return &data_ov001_020a0528->actors[index];
    }
    return 0;
}
