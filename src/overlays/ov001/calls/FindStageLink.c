#include "nitro/types.h"

typedef struct StageLink {
    u16 id;
    u8 pad_02[6];
} StageLink;

typedef struct StageManager {
    u8 pad_00000[0x8];
    StageLink links[1];
    u8 pad_00010[0x18dec - 0x10];
    u16 linkCount;
} StageManager;

extern StageManager *data_ov001_020a0528;

StageLink *FindStageLink(u32 id)
{
    u16 index;

    for (index = 0; index < data_ov001_020a0528->linkCount; index++) {
        if (id == data_ov001_020a0528->links[index].id) {
            return &data_ov001_020a0528->links[index];
        }
    }
    return NULL;
}
