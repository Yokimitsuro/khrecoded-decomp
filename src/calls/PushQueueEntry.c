#include "nitro/types.h"

typedef struct QueueEntry {
    u32 value;
    u16 extra;
} QueueEntry;

typedef struct QueueOwner {
    u8 pad_0000[0x6028];
    int capacity;
    int count;
    u8 pad_6030[4];
    QueueEntry entries[1];
} QueueOwner;

BOOL PushQueueEntry(QueueOwner *owner, const QueueEntry *entry)
{
    int count = owner->count;
    BOOL pushed = FALSE;

    if (count < owner->capacity) {
        owner->entries[count].value = entry->value;
        owner->entries[count].extra = entry->extra;
        pushed = TRUE;
        owner->count++;
    }
    return pushed;
}
