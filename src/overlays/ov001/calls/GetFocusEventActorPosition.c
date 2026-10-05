#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageEventRecord {
    u8 pad_00[0x10];
    u16 actorId;
} StageEventRecord;

typedef struct StageActor {
    u8 pad_000[0x2c0];
    VecFx32 position;
} StageActor;

typedef struct StageManager {
    u8 pad_00000[0x18f48];
    u16 focusEventId;
} StageManager;

extern StageManager *data_ov001_020a0528;

extern StageActor *GetStageActor(int id);
extern StageEventRecord *GetStageEventRecord(u32 id);

BOOL GetFocusEventActorPosition(VecFx32 *out)
{
    StageEventRecord *record;
    StageActor *actor;

    if (data_ov001_020a0528->focusEventId == 0) {
        return FALSE;
    }
    record = GetStageEventRecord(data_ov001_020a0528->focusEventId);
    if (record == NULL) {
        return FALSE;
    }
    if (record->actorId == 0) {
        return FALSE;
    }
    actor = GetStageActor((s16)record->actorId);
    if (actor == NULL) {
        return FALSE;
    }
    if (out != NULL) {
        *out = actor->position;
    }
    return TRUE;
}
