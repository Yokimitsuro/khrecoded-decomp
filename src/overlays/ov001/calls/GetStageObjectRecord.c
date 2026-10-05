#include "nitro/types.h"

typedef struct {
    u8 data[0x124];
} StageObjectRecord;

typedef struct {
    u8 pad_00[0x214];
    StageObjectRecord records[1];
} StageManager;

extern StageManager *data_ov001_020a0528;

StageObjectRecord *GetStageObjectRecord(u32 id)
{
    u32 index = (id - 1) & 0xffff;

    if (data_ov001_020a0528 != 0) {
        return &data_ov001_020a0528->records[index];
    }
    return 0;
}
