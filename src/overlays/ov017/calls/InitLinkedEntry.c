#include "nitro/types.h"

typedef struct LinkedEntry {
    u8 kind;
    u8 flags;
    u16 value;
    struct LinkedEntry *next;
} LinkedEntry;

void InitLinkedEntry(LinkedEntry *entry, u8 kind, u8 flags, u16 value)
{
    entry->kind = kind;
    entry->flags = flags | 2;
    entry->value = value;
    entry->next = (entry->flags & 1) ? entry : NULL;
}
