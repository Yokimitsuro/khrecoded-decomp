#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u16 seqArcId;
    u16 soundId;
    u32 handle;
} StageSoundSlot;

typedef struct {
    u8 pad_00[0x18b78];
    StageSoundSlot soundSlots[64];
    u8 pad_18d78[0x18df0 - 0x18d78];
    u16 soundCursor;
} StageManager;

extern StageManager *data_ov001_020a0528;
extern u32 PlayStageSoundAt(s32 seqArcId, s32 soundId, VecFx32 *position, u32 flags);

u8 PlayTrackedStageSound(s32 seqArcId, s32 soundId, VecFx32 *position, u32 flags)
{
    u32 handle;
    u8 attempt;
    StageSoundSlot *slot;

    handle = PlayStageSoundAt(seqArcId, soundId, position, flags);
    if (handle != 0) {
        for (attempt = 0; attempt < 64; attempt++) {
            slot = &data_ov001_020a0528->soundSlots[data_ov001_020a0528->soundCursor];
            if (slot->handle == 0) {
                slot->handle = handle;
                slot->seqArcId = seqArcId;
                slot->soundId = soundId;
                return data_ov001_020a0528->soundCursor + 1;
            }
            data_ov001_020a0528->soundCursor = (data_ov001_020a0528->soundCursor + 1) % 64;
        }
    }
    return 0;
}
