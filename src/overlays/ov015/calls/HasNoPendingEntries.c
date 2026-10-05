#include "nitro/types.h"

typedef struct CursorEntry {
    s16 state;
    u8 pad_02[0x16];
} CursorEntry;

typedef struct CursorState {
    u8 pad_00[0x55];
    s8 entryCount;
    u8 pad_56[0x84 - 0x56];
    CursorEntry entries[1];
} CursorState;

extern CursorState *data_ov015_020812e0;

BOOL HasNoPendingEntries(void)
{
    int i;
    int count;
    BOOL result = TRUE;
    CursorState *cursor = data_ov015_020812e0;

    count = cursor->entryCount;

    for (i = 0; i < count; i++) {
        if (cursor->entries[i].state == 2) {
            result = FALSE;
        }
    }
    return result;
}
