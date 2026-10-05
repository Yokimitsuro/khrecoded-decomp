#include "nitro/types.h"

typedef struct SoundQueueEntry {
    u8 kind;
    u8 arg;
    u16 value;
} SoundQueueEntry;

extern char *data_0206084c;
SoundQueueEntry *GetRecentHistoryEntry(int age);
void PushSoundQueueEntry(int kind, int arg, u16 value);

void QueueSoundRequest(int kind, int arg, int value)
{
    SoundQueueEntry *entry;

    if (*(s16 *)(data_0206084c + 0xb472a) == arg && *(u8 *)(data_0206084c + 0xb47d3) == 0)
        return;

    /* Update the newest pending request of this kind */
    entry = GetRecentHistoryEntry(0);
    if (entry == NULL || entry->kind != kind) {
        PushSoundQueueEntry(kind, arg, (u16)value);
        return;
    }
    entry->arg = arg;
    entry->value = value;
}
