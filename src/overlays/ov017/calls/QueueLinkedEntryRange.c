#include "nitro/types.h"

typedef struct LinkedEntry {
    u8 kind;
    u8 flags;
    u16 value;
    struct LinkedEntry *next;
} LinkedEntry;

typedef struct FieldObject {
    u8 pad_00[0x60];
    LinkedEntry *entries;
} FieldObject;

extern void FormatAndQueueMessage(void *queue, u32 kind, u32 flags, u32 value);

void QueueLinkedEntryRange(void *queue, FieldObject *object, int first, int last)
{
    LinkedEntry *entry = object->entries;
    int i;

    for (i = 0; i <= last; i++) {
        if (i >= first) {
            FormatAndQueueMessage(queue, entry->kind, entry->flags, entry->value);
        }
        entry = entry->next;
    }
}
