#include "nitro/types.h"

typedef struct SlotEntry {
    s16 id;
    u8 pad02[2];
    u8 state;
    u8 pad05[7];
} SlotEntry;

extern SlotEntry data_020608e0[8];
void func_ov001_0206459c(int bitOffset, u32 bitCount, u32 value);

void SaveSlotEntriesToBits(void)
{
    int i = 0;
    int bitOffset = 0x3729;
    /* Empty slots are written as zero */
    do {
        SlotEntry *entry = &data_020608e0[i];
        u32 id = 0;
        u32 state = 0;
        if (entry->id != -1) {
            state = entry->state;
            id = entry->id - 0xca;
        }
        func_ov001_0206459c(bitOffset, 4, id);
        func_ov001_0206459c(bitOffset + 4, 9, state);
        i++;
        bitOffset += 0xd;
    } while (i < 8);
}
