#include "nitro/types.h"

extern int data_ov086_020c2360[];
extern BOOL func_ov001_020645c8(u32 flagId);
extern int CountGroupEntriesInStateOne(int entryIndex);

int SumUnlockedGroupEntryCounts(int groupIndex)
{
    int total;
    int firstEntry;
    int i;
    int entryCount;
    int entryIndex;

    firstEntry = 0;
    total = 0;

    for (i = 0; i < groupIndex; i++) {
        firstEntry += data_ov086_020c2360[i];
    }
    entryCount = data_ov086_020c2360[groupIndex];
    for (i = 0; i < entryCount; i++) {
        entryIndex = firstEntry + i;
        if (func_ov001_020645c8(entryIndex + 0x581)) {
            total += CountGroupEntriesInStateOne(entryIndex);
        }
    }
    return total;
}
