#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollSegment {
    VecFx32 start;
} CollSegment;

typedef struct CollSweep {
    CollSegment *segment;
    u8 pad_04[0x18];
    s32 kind;
    VecFx32 delta;
} CollSweep;

typedef struct ContactPlane {
    s32 distance;
    VecFx32 normal;
    s32 time;
    u8 surfaceType;
    u8 pad_15[3];
} ContactPlane;

typedef struct ContactEntry {
    void *target;
    s32 field;
    u8 surfaceType;
    u8 pad_09[3];
} ContactEntry;

typedef struct Mover {
    u8 pad_00[0x7c];
    u8 tracksMotion;
    u8 pad_7d[0x33];
    CollSweep *sweep;
} Mover;

extern const VecFx32 data_0205344c;
extern s32 RecordContactPlane(Mover *mover, s32 index, ContactPlane *planes, ContactEntry *entries, ContactEntry *entry, BOOL *moving);

static inline BOOL StopSweepAt(Mover *mover, const VecFx32 *position)
{
    if (mover->tracksMotion) {
        mover->sweep->delta = data_0205344c;
    }
    mover->sweep->segment->start = *position;
    return TRUE;
}

BOOL RecordHitContact(void *target, ContactEntry *entry, ContactEntry *entries, Mover *mover, ContactPlane *planes, u8 *planeIndex, s32 unused6, BOOL *moving, s32 unused8, void **hitTargets, s32 unused10, u8 *hitCount, const VecFx32 *position)
{
    u8 count = *hitCount;

    if (count == 16) {
        return StopSweepAt(mover, position);
    }
    *hitCount = count + 1;
    hitTargets[count] = target;
    entry->target = target;
    if (planes != NULL) {
        if (!*moving && mover->sweep->kind != 2) {
            planes[*planeIndex].time = -1;
        }
        entry->surfaceType = planes[*planeIndex].surfaceType;
    }
    switch (RecordContactPlane(mover, *planeIndex, planes, entries, entry, moving)) {
    case 0:
        break;
    case 1:
        if (++*planeIndex == 16) {
            return StopSweepAt(mover, position);
        }
        break;
    case 2:
        return TRUE;
    }
    return FALSE;
}
