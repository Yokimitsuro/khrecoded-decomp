#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2a];
    s16 linkedId;
    s32 trackedIndex;
} TrackedRecordEntry;

extern void func_ov058_020d4520(TrackedRecordEntry *entry);

void InitTrackedRecordEntry(TrackedRecordEntry *entry)
{
    func_ov058_020d4520(entry);
    entry->linkedId = -1;
    entry->trackedIndex = -1;
}
