#include "nitro/types.h"

extern int data_ov086_020c2360[];
extern BOOL func_ov001_020645c8(u32 flagId);

int CountUnlockedGroupEntries(int groupIndex)
{
    int entryCount;
    int entry;
    int i;
    int unlocked;
    int firstEntry;

    firstEntry = 0;
    unlocked = 0;
    for (i = 0; i < groupIndex; i++) {
        firstEntry += data_ov086_020c2360[i];
    }
    entryCount = data_ov086_020c2360[groupIndex];
    for (entry = 0; entry < entryCount; entry++) {
        if (func_ov001_020645c8(firstEntry + 0x9b0 + entry)) {
            unlocked++;
        }
    }
    return unlocked;
}
