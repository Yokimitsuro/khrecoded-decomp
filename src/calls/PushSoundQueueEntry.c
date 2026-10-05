#include "nitro/types.h"

typedef struct SoundQueueEntry {
    u8 kind;
    u8 arg;
    u16 value;
} SoundQueueEntry;

extern u8 *gSoundWork;

void PushSoundQueueEntry(u8 kind, u8 arg, u16 value)
{
    u8 *work = gSoundWork;
    int slot = (work[0xb47d2] + work[0xb47d3]) % 4;
    SoundQueueEntry *entry = (SoundQueueEntry *)(work + 0xb47c2) + slot;

    entry->kind = kind;
    entry->arg = arg;
    entry->value = value;
    work[0xb47d3]++;
}
