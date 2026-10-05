#include "nitro/types.h"

typedef struct {
    u8 unk_00;
    u8 count;
    u8 pad_02[0x2];
} EventSide;

typedef struct {
    s8 sideCount;
    u8 pad_01[0x3];
    EventSide sides[1];
} EventGroup;

typedef struct {
    u8 pad_00[0xc];
    EventGroup *groups[1];
} EventGroupTable;

typedef struct {
    u8 pad_00[0x18df8];
    EventGroupTable *eventGroups;
} StageManager;

typedef struct {
    u8 groupIndex;
} LargeTableEntry;

typedef struct {
    u8 pad_00[0x6];
    u16 flagsLow : 7;
    u16 hidden : 1;
    u16 flagsHigh : 8;
    u8 pad_08[0x68];
    s32 remaining;
} StageEventRecord;

typedef struct {
    u16 entryId;
    u8 pad_02[0x8];
    s16 firstEvent;
    u8 pad_0C[0x2];
    u8 chosenSide;
} StageEventPicker;

extern StageManager *data_ov001_020a0528;

extern LargeTableEntry *GetLargeTableEntry(u16 entryId);
extern u32 random_next_scaled(u32 upperBound);
extern StageEventRecord *GetStageEventRecord(u16 eventId);

void PickStageEventSide(StageEventPicker *picker) {
    EventGroupTable *table = data_ov001_020a0528->eventGroups;
    EventGroup *group = table->groups[GetLargeTableEntry(picker->entryId)->groupIndex];
    u16 eventId = picker->firstEvent + 1;
    u16 active;
    u16 i;
    u16 j;
    u16 side;
    EventSide *entry;
    StageEventRecord *record;

    if (picker->chosenSide != 0) {
        return;
    }
    side = random_next_scaled(100) >= 20 ? 1 : 0;
    entry = &group->sides[side];
    active = 0;
    for (j = 0; j < entry->count; j++) {
        record = GetStageEventRecord(eventId);
        if (record != NULL && record->remaining > 0) {
            active++;
        }
    }
    if (active == 0) {
        side = side == 1 ? 0 : 1;
    }
    for (i = 0; i < group->sideCount; i++) {
        entry = &group->sides[i];
        for (j = 0; j < entry->count; j++) {
            record = GetStageEventRecord(eventId);
            record->hidden = FALSE;
            if (record != NULL && side != i) {
                record->hidden = TRUE;
            }
            eventId++;
        }
    }
    picker->chosenSide = side + 1;
}
