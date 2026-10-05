#include "nitro/types.h"

typedef struct {
    u8 data[0x10];
} HitShape;

typedef struct {
    u8 pad_00[0x21];
    s8 state;
    u8 type : 3;
    u8 mirrored : 1;
    u8 reserved : 4;
    s8 shapeIndex;
    u8 pad_24[0x20];
    HitShape shape;
} HitEntry;

typedef struct {
    u8 pad_00[0x18];
    u16 primary : 1;
    u16 bit1 : 1;
    u16 bit2 : 1;
    u16 forced : 1;
    u16 mirrored : 1;
    u16 linked : 1;
    u16 reserved : 10;
    u8 pad_1a[4];
    u8 state;
    u8 pad_1f;
} SlotEntry;

typedef struct {
    u8 pad_00[0x30];
    int state;
    u8 pad_34[8];
    u32 flags;
    u8 pad_40[2];
    s16 entryCount;
    HitEntry *entries;
    u8 pad_48[4];
    u16 reserved0 : 4;
    u16 primary : 1;
    u16 linked : 1;
    u16 reserved6 : 10;
    HitShape shapes[1];
} Target;

typedef struct {
    u8 pad_0000[0x9ac];
    u64 stateFlags;
} Actor;

extern int ScanAttackHits(Actor *actor, HitEntry *hit, HitShape *shape, SlotEntry *entry);
extern int RunVolumeHitScan(Actor *actor, HitEntry *hit, HitShape *shape, SlotEntry *entry);
extern int DispatchHitEvent(Actor *actor, HitEntry *hit, HitShape *shape, SlotEntry *entry);

int ProcessTargetHitEntries(Actor *actor, Target *target, SlotEntry *entry)
{
    int result = 0;
    HitShape *shape;
    int i;

    if (target->flags & 2) {
        shape = target->shapes;
    }
    for (i = 0; i < target->entryCount && result != 1; i++) {
        HitEntry *hit = &target->entries[i];
        if (!(target->flags & 2)) {
            if (hit->shapeIndex < 0) {
                shape = &hit->shape;
            } else {
                shape = &target->shapes[hit->shapeIndex];
            }
        }
        entry->mirrored = hit->mirrored;
        entry->state = target->state;
        if (hit->state >= 0) {
            entry->state = hit->state;
        }
        switch (hit->type) {
        case 0:
            result = ScanAttackHits(actor, hit, shape, entry);
            break;
        case 1:
            result = RunVolumeHitScan(actor, hit, shape, entry);
            break;
        case 2:
            result = DispatchHitEvent(actor, hit, shape, entry);
            break;
        }
    }
    target->linked = entry->linked;
    target->primary = entry->primary;
    if (result == 0 && !(actor->stateFlags & 0x4000000)) {
        if (entry->primary) {
            actor->stateFlags |= 0x4000000;
        }
        if (entry->forced) {
            actor->stateFlags |= 0x4000000;
        }
    }
    return result;
}
