#include "nitro/types.h"

typedef struct SlotEntry {
    s16 id;
    u8 pad_02[2];
    u8 state;
    u8 level;
    u8 pad_06[6];
} SlotEntry;

extern SlotEntry data_020608e0[];

void ResetSlotEntries(void)
{
    int i;

    for (i = 0; i < 8; i++) {
        data_020608e0[i].id = -1;
        data_020608e0[i].level = 99;
        data_020608e0[i].state = 0;
    }
}
