#include "nitro/types.h"

typedef struct SlotEntry {
    s16 id;
    u8 pad02[2];
    u8 state;
    u8 pad05[7];
} SlotEntry;

extern SlotEntry data_020608e0[8];
int func_ov001_02064574(u32 bitOffset, int bitCount);

void LoadSlotEntriesFromBits(void)
{
    int i = 0;
    u32 bitOffset = 0x3729;
    /* Each packed record is 13 bits wide */
    do {
        SlotEntry *entry = &data_020608e0[i];
        int id;
        int state;
        entry->id = -1;
        entry->state = 0;
        id = func_ov001_02064574(bitOffset, 4);
        state = func_ov001_02064574(bitOffset + 4, 9);
        bitOffset += 0xd;
        if (id > 0) {
            entry->id = id + 0xca;
            entry->state = state;
        }
        i++;
    } while (i < 8);
}


