#include "nitro/types.h"

typedef struct {
    s16 id;
    u8 pad_02[6];
    s8 state;
    u8 pad_09[3];
} RecordEntryDef;

extern RecordEntryDef data_ov086_020c23c0[];

int CountGroupEntriesInStateOne(int group)
{
    u32 i;
    int count;
    int total;
    RecordEntryDef *entry;

    total = 0;
    entry = NULL;
    count = -1;

    for (i = 0; i < 0x103; i++) {
        if (data_ov086_020c23c0[i].id == -1 && ++count == group) {
            entry = &data_ov086_020c23c0[i + 1];
            break;
        }
    }
    if (entry == NULL) {
        return 0;
    }
    for (; entry->id != -1; entry++) {
        if (entry->state == 1) {
            total++;
        }
    }
    return total;
}
