#include "nitro/types.h"

extern u8 *data_0205fe0c;
extern u16 data_0205fec4[];
extern u16 gRecordCounters[2];

typedef struct RecordEntry
{
    u16 unk_00;
    union
    {
        u16 flags;
        struct
        {
            u16 active : 1;
            u16 pad_1 : 7;
            u16 category : 8;
        };
    };
} RecordEntry;

void ReleaseRecordEntry(int index)
{
    RecordEntry *entry = (RecordEntry *)(data_0205fe0c + 0x2e00 + index * 4);

    entry->active = 0;
    data_0205fec4[entry->category] -= 1;
    gRecordCounters[0] -= 1;
}
