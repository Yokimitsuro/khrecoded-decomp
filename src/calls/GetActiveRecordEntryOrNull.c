#include "nitro/types.h"

extern u8 *data_0205fe0c;

typedef struct RecordEntry
{
    u16 unk_00;
    u16 active : 1;
} RecordEntry;

RecordEntry *GetActiveRecordEntryOrNull(int index)
{
    RecordEntry *entry = (RecordEntry *)(data_0205fe0c + 0x2e00 + index * 4);
    if (!entry->active)
    {
        return NULL;
    }
    return entry;
}
