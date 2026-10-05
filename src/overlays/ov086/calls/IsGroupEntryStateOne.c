#include "nitro/types.h"

typedef struct {
    s16 id;
    u8 pad_02[6];
    s8 state;
    u8 pad_09[3];
} RecordEntryDef;

extern RecordEntryDef data_ov086_020c23c0[];

BOOL IsGroupEntryStateOne(int group, int index)
{
    u32 i;
    int count = -1;
    RecordEntryDef *found = NULL;

    for (i = 0; i < 0x103; i++) {
        if (data_ov086_020c23c0[i].id == -1 && ++count == group) {
            found = &data_ov086_020c23c0[i + 1];
            break;
        }
    }
    if (found == NULL) {
        return FALSE;
    }
    return found[index].state == 1;
}
