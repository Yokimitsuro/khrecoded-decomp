#include "nitro/types.h"

typedef struct {
    s32 time;
    void *handle;
    u8 pad_08[6];
    s8 channel;
    s8 ownsHandle : 1;
    s8 pad_bits : 7;
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

extern CueGroup *FindTableEntryById(CueTable *table, int id);
extern void StopSoundSeqHandle(void *handle);

void StopCueGroupSounds(CueTable *table, int groupId)
{
    CueGroup *group;
    int i;

    if (groupId == table->groupId) {
        return;
    }
    group = FindTableEntryById(table, table->groupId);
    if (group == NULL) {
        return;
    }
    for (i = 0; i < group->itemCount; i++) {
        CueItem *item = group->items[i];
        if (item->ownsHandle && item->handle != NULL) {
            StopSoundSeqHandle(item->handle);
        }
        item->handle = NULL;
        item->channel = -1;
        if (table->current == &item->handle) {
            table->current = NULL;
        }
    }
}
