#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x288a];
    u16 entryFlags[1];
} SaveData;

extern int data_ov086_020c2360[];
extern SaveData *data_0205fe0c;
extern BOOL func_ov001_020645c8(u32 flagId);
extern BOOL IsGroupEntryStateOne(int group, int index);

int CountGroupFlaggedEntries_020bf4a4(int groupIndex)
{
    int firstEntry;
    u32 bit;
    int total;
    int entryIndex;
    int entry;
    int entryCount;
    int i;

    firstEntry = 0;
    total = 0;
    for (i = 0; i < groupIndex; i++) {
        firstEntry += data_ov086_020c2360[i];
    }
    entryCount = data_ov086_020c2360[groupIndex];
    for (entry = 0; entry < entryCount; entry++) {
        entryIndex = firstEntry + entry;
        if (func_ov001_020645c8(entryIndex + 0x581)) {
            for (bit = 0; bit < 16; bit++) {
                if ((data_0205fe0c->entryFlags[entryIndex] & (1 << bit)) && IsGroupEntryStateOne(entryIndex, bit)) {
                    total++;
                }
            }
        }
    }
    return total;
}
