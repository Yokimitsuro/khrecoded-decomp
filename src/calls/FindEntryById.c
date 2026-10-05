#include "nitro/types.h"

typedef struct IdEntry {
    u32 id : 18;
    u32 flags : 14;
} IdEntry;

typedef struct IdList {
    IdEntry *entries;
    u8 count;
} IdList;

IdEntry *FindEntryById(IdList *list, u32 id)
{
    IdEntry *found = NULL;
    int i;

    if (id == (u32)-1) {
        return found;
    }
    for (i = 0; i < list->count; i++) {
        if (id == list->entries[i].id) {
            found = &list->entries[i];
            break;
        }
    }
    return found;
}
