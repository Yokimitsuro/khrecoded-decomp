#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageData {
    u32 flags;
    u8 pad_00004[0x18e4c];
    VecFx32 origin;
} StageData;

extern StageData *data_ov001_020a0528;
extern const VecFx32 data_0205344c;

void ResetStageOrigin(void)
{
    if (data_ov001_020a0528 != NULL) {
        data_ov001_020a0528->flags |= 1;
        data_ov001_020a0528->origin = data_0205344c;
    }
}
