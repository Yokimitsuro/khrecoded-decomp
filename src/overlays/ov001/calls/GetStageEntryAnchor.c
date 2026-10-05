#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageEntry {
    u8 pad_00[0x10];
    VecFx32 position;
    u8 pad_1C[0x4];
} StageEntry;

typedef struct StageManager {
    u8 pad_00000[0x18a94];
    StageEntry entries[1];
} StageManager;

extern const VecFx32 data_0205344c;
extern StageManager *data_ov001_020a0528;
extern s32 func_ov001_0206dc38(void);
extern VecFx32 *func_ov001_0206dc60(u32 index);

void GetStageEntryAnchor(u32 id, VecFx32 *outPosition)
{
    u32 index;

    *outPosition = data_0205344c;
    index = (id - 1) & 0xffff;
    if (data_ov001_020a0528 == NULL || outPosition == NULL) {
        return;
    }
    *outPosition = data_ov001_020a0528->entries[index].position;
    outPosition->y += 0x99a;
    if (id == 0) {
        return;
    }
    if (index >= 3) {
        return;
    }
    if (func_ov001_0206dc38() <= 0) {
        return;
    }
    *outPosition = *func_ov001_0206dc60(index);
}
