#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct RangeFx32 {
    fx32 min;
    fx32 max;
} RangeFx32;

typedef struct RangeTable {
    RangeFx32 ranges[4];
} RangeTable;

typedef struct SaveData {
    u8 pad_0000[0x2c62];
    u8 difficulty;
} SaveData;

typedef struct StageActor {
    u8 pad_000[0x28c];
    u16 flagsLow : 11;
    u16 nearestEntry : 3;
    u16 flagsHigh : 2;
    u8 pad_28e[0x32];
    VecFx32 position;
} StageActor;

typedef struct DelayedSpawner {
    u8 pad_000[0x10];
    u16 actorId;
    u8 pad_012[0x52];
    fx32 minScale;
    fx32 maxScale;
    u8 pad_06c[0x134];
    s32 nextTime;
} DelayedSpawner;

extern const RangeTable data_ov001_0209e4bc;
extern SaveData *data_0205fe0c;
extern int FX_Mul(int left, int right);
extern u32 random_next_scaled(u32 upperBound);
extern StageActor *GetStageActor(s16 groupId);
extern u16 FindNearestStageEntry(const VecFx32 *target);
extern StageActor *GetLinkedStageActor(StageActor *actor);

void ScheduleSpawnerNextTime(DelayedSpawner *spawner, int baseTime)
{
    RangeTable table;
    int difficulty;
    int low;
    int high;
    StageActor *actor;
    u16 nearest;

    table = data_ov001_0209e4bc;
    difficulty = data_0205fe0c->difficulty;
    low = baseTime + FX_Mul(spawner->minScale, table.ranges[difficulty].min);
    high = baseTime + FX_Mul(spawner->maxScale, table.ranges[difficulty].max);
    spawner->nextTime = low + random_next_scaled(high - low);
    if (spawner->actorId == 0) {
        return;
    }
    actor = GetStageActor(spawner->actorId);
    if (actor == NULL) {
        return;
    }
    actor->nearestEntry = 0;
    if (actor->nearestEntry != 0) {
        return;
    }
    nearest = FindNearestStageEntry(&actor->position);
    while (actor != NULL) {
        actor->nearestEntry = nearest;
        actor = GetLinkedStageActor(actor);
    }
}
