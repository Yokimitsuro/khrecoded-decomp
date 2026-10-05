#include "nitro/types.h"

extern int NestedPointer_GetFirstWord(int *objectBase, int recordIndex, int entryIndex);
extern int strcmp(const char *a, const char *b);

int FindNameIndexInTable(int *objectBase, const char *name)
{
    int i = 0;
    u16 *table;
    int count;
    int cmpResult;

    table = (u16 *)NestedPointer_GetFirstWord(objectBase, 0, 0);
    count = *table;
    if (count > 0) {
        do {
            cmpResult = strcmp(name, (char *)table + table[i + 1]);
            if (cmpResult == 0) {
                return i;
            }
            i++;
        } while (i < count);
    }
    return -1;
}
