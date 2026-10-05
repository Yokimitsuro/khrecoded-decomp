#include "nitro/types.h"

typedef struct {
    s32 time;
    void *link;
    u8 pad_08[6];
    u8 active;
} CueItem;

typedef struct {
    s16 id;
    s16 itemCount;
    CueItem **items;
} CueGroup;

typedef struct {
    u8 pad_00[0x20];
    s32 groupId;
    void **current;
} CueTable;

extern void StopCueGroupSounds(CueTable *table, int groupId, s32 time);
extern CueGroup *FindTableEntryById(CueTable *table, int id);

void ResetCueGroupBefore(CueTable *table, int groupId, s32 time)
{
    CueGroup *group;
    int i;

    StopCueGroupSounds(table, -1, time);
    table->groupId = groupId;
    group = FindTableEntryById(table, groupId);
    if (group == NULL) {
        return;
    }
    for (i = 0; i < group->itemCount; i++) {
        CueItem *item = group->items[i];
        if (item->time < time) {
            item->active = 0;
            item->link = NULL;
            if (table->current == &item->link) {
                table->current = NULL;
            }
        }
    }
}
