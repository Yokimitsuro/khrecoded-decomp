#include "nitro/types.h"

typedef struct {
    u8 kind;
    u8 pad_001[7];
    u32 flags;
    u8 pad_00c[0xd0];
    s16 score;
    u8 pad_0de[0x16];
    s32 points;
    u16 bonus;
    u8 pad_0fa[0x3ba];
} StageEntry;

typedef struct {
    u8 pad_00[8];
    u32 flags;
    u8 pad_0c[8];
    StageEntry *entries;
    u8 entryCount;
    u8 playerCount;
} StageWork;

typedef struct {
    s32 primary;
    s32 secondary;
    s32 tertiary;
    s32 totalPoints;
    s32 totalBonus;
} StageTotals;

void SumStageTotals(StageWork **workRef, StageTotals *totals) {
    StageWork *work = *workRef;
    int i;

    for (i = 0; i < work->entryCount; i++) {
        StageEntry *entry = &work->entries[i];
        s16 score = entry->score;
        switch (entry->kind) {
        case 0xff:
            totals->primary = score;
            break;
        case 0xfe:
            totals->secondary = score;
            break;
        case 0xfd:
            totals->tertiary = score;
            break;
        }
    }
    if (totals->primary <= 0) {
        totals->primary = 1;
    }
    if (work->flags & 0x2000) {
        totals->totalPoints = 0;
        totals->totalBonus = 0;
        for (i = work->playerCount; i < work->entryCount; i++) {
            if ((work->entries[i].flags & 0x80000) == 0) {
                totals->totalPoints += work->entries[i].points;
                totals->totalBonus += work->entries[i].bonus;
            }
        }
        if (work->flags & 0x20) {
            totals->totalPoints = 0;
        }
    } else {
        totals->totalPoints = 0;
        totals->totalBonus = 0;
    }
}
