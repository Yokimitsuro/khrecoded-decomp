#include "nitro/types.h"

typedef struct GroupTableEntry {
    s16 id;
    u8 pad_02[6];
    s8 state;
    u8 pad_09[3];
} GroupTableEntry;

extern GroupTableEntry data_ov001_0209f62c[];

int CountGroupFlaggedEntries(int group)
{
    u32 i;
    int count = 0;
    int separatorCount = 0;
    GroupTableEntry *entry = NULL;

    for (i = 0; i < 0x103; i++) {
        if (data_ov001_0209f62c[i].id == -1) {
            if (++separatorCount == group) {
                entry = &data_ov001_0209f62c[i + 1];
                break;
            }
        }
    }
    if (entry == NULL) {
        return 0;
    }
    while (entry->id != -1) {
        if (entry->state == 1) {
            count++;
        }
        entry++;
    }
    return count;
}
