#include "nitro/types.h"

typedef struct LinkedEntry {
    u8 kind;
    u8 flags;
    u16 value;
    struct LinkedEntry *next;
} LinkedEntry;

LinkedEntry *FindLastLoopEntry(LinkedEntry *entry)
{
    if (entry == NULL) {
        return NULL;
    }
    while (entry->next != NULL && !(entry->flags & 1)) {
        entry = entry->next;
    }
    if (!(entry->flags & 1)) {
        return NULL;
    }
    return entry;
}
