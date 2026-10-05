#include "nitro/types.h"

typedef struct EntryList {
    u8 pad_0000[0x4582];
    u8 locked;
} EntryList;

extern void BuildRecordCountList_020c1994(EntryList *list);

void RefreshEntryListIfUnlocked(EntryList *list)
{
    if (list->locked == 0) {
        BuildRecordCountList_020c1994(list);
    }
}
