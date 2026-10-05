#include "nitro/types.h"

typedef struct StageEntry {
    u8 pad_00[0x1c];
    u32 param;
} StageEntry;

typedef struct StageManager {
    u8 pad_00000[0x18a94];
    StageEntry entries[1];
} StageManager;

extern StageManager *data_ov001_020a0528;

u32 GetStageEntryParam(u32 id)
{
    u32 index = (id - 1) & 0xffff;

    if (data_ov001_020a0528 != NULL) {
        return data_ov001_020a0528->entries[index].param;
    }
    return 0;
}
