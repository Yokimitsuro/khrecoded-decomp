#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2a];
    s16 linkedId;
    s32 trackedIndex;
} TrackedRecordEntry;

extern void InitRecordEntry(TrackedRecordEntry *entry);

void InitTrackedRecordEntry(TrackedRecordEntry *entry)
{
    InitRecordEntry(entry);
    entry->linkedId = -1;
    entry->trackedIndex = -1;
}
