#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StateBlock {
    u8 pad_00[0xcc];
} StateBlock;

typedef struct TrackingOwner {
    u8 pad_000[0x119];
    u8 hasTracker;
    u8 pad_11a[0x174 - 0x11a];
    struct TrackingState *tracker;
    u32 trackerActive;
} TrackingOwner;

typedef struct TrackingState {
    TrackingOwner *owner;
    u32 flags;
    VecFx32 velocity;
    VecFx32 origin;
    VecFx32 position;
    u32 minValue;
    u32 unk_30;
    u32 unk_34;
    u16 unk_38;
    s16 id;
    u8 kind;
    u8 pad_3d[3];
    u32 maxValue;
    StateBlock state;
    u32 unk_110;
    u8 pad_114[0x2c4 - 0x114];
    u8 history[0x18];
} TrackingState;

extern VecFx32 data_0205344c;
extern u8 data_02060780;
extern void ClearStateBlock(StateBlock *block);
extern void MIi_CpuClear32(int value, void *dst, int size);

BOOL InitTrackingState(TrackingState *tracker, TrackingOwner *owner)
{
    tracker->id = -1;
    tracker->owner = owner;
    tracker->flags = 0;
    tracker->flags = 0x10 | tracker->flags;
    tracker->origin = data_0205344c;
    ClearStateBlock(&tracker->state);
    tracker->velocity.x = tracker->velocity.y = tracker->velocity.z = 0;
    tracker->position.x = tracker->position.y = tracker->position.z = 0;
    tracker->minValue = 0x80000000;
    tracker->unk_30 = 0x80;
    tracker->unk_34 = 0x2000;
    tracker->unk_110 = 0x1000;
    tracker->unk_38 = 0x666;
    tracker->flags |= 4;
    tracker->owner->hasTracker = 1;
    tracker->owner->trackerActive = 1;
    tracker->owner->tracker = tracker;
    tracker->kind = data_02060780;
    MIi_CpuClear32(0, tracker->history, sizeof(tracker->history));
    tracker->maxValue = 0x7fffffff;
    return TRUE;
}
