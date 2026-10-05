#include "nitro/types.h"

typedef struct LinkedEntry {
    u8 kind;
    u8 flags;
    u16 value;
    struct LinkedEntry *next;
} LinkedEntry;

LinkedEntry *FindLinkedEntryTail(LinkedEntry *entry)
{
    if (entry == NULL) {
        return NULL;
    }
    while (entry->next != NULL && !(entry->flags & 2)) {
        entry = entry->next;
    }
    return entry;
}
