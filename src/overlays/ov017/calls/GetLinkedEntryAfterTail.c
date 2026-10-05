#include "nitro/types.h"

typedef struct LinkedEntry {
    u8 kind;
    u8 flags;
    u16 value;
    struct LinkedEntry *next;
} LinkedEntry;

extern LinkedEntry *FindLinkedEntryTail(LinkedEntry *entry);

LinkedEntry *GetLinkedEntryAfterTail(LinkedEntry *entry)
{
    return FindLinkedEntryTail(entry)->next;
}
