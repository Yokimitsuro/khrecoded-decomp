#include "nitro/types.h"

typedef struct PanelEntry {
    s16 level;
    u16 flags;
    s16 id;
    u8 pad_06[0x12];
} PanelEntry;

typedef struct PanelWork {
    u8 pad_0000[0x55];
    s8 entryCount;
    u8 pad_0056[0x2e];
    PanelEntry entries[1];
} PanelWork;

extern PanelWork *data_ov015_020812e0;

BOOL MarkPendingEntryById(int id)
{
    PanelWork *work = data_ov015_020812e0;
    BOOL found = FALSE;
    int i;

    for (i = 0; i < work->entryCount; i++) {
        if (id == work->entries[i].id && work->entries[i].level >= 2 && !(work->entries[i].flags & 1)) {
            work->entries[i].flags |= 1;
            found = TRUE;
            break;
        }
    }
    return found;
}
