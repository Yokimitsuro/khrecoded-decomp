#include "nitro/types.h"

typedef struct GroupTableEntry {
    s16 id;
    u8 pad_02[6];
    s8 state;
    u8 pad_09[3];
} GroupTableEntry;

extern GroupTableEntry data_ov001_0209f62c[];

BOOL IsGroupEntryFlagged(int group, int index)
{
    u32 i;
    int separatorCount = 0;
    GroupTableEntry *groupStart = NULL;

    for (i = 0; i < 0x103; i++) {
        if (data_ov001_0209f62c[i].id == -1) {
            if (++separatorCount == group) {
                groupStart = &data_ov001_0209f62c[i + 1];
                break;
            }
        }
    }
    if (groupStart == NULL) {
        return FALSE;
    }
    if (groupStart[index].state == 1) {
        return TRUE;
    }
    return FALSE;
}
