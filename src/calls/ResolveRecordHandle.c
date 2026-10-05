#include "nitro/types.h"

extern u8 *data_0205fe0c;

typedef struct RecordEntry
{
    u16 unk_00;
    union
    {
        u16 flags;
        u16 active : 1;
    };
} RecordEntry;

extern RecordEntry *GetActiveRecordEntryOrNull(int index);

BOOL ResolveRecordHandle(int index, RecordEntry *entry, u32 *outValue)
{
    u16 handle;
    RecordEntry *source;

    entry->active = 0;
    *outValue = 0xffffffff;

    handle = *(u16 *)(data_0205fe0c + index * 2 + 0x2d84);
    if (handle == 0xffff)
    {
        return FALSE;
    }
    if (handle < 0x200)
    {
        *outValue = handle;
        return TRUE;
    }
    source = GetActiveRecordEntryOrNull((handle - 0x200) & 0xffff);
    entry->unk_00 = source->unk_00;
    entry->flags = source->flags;
    return TRUE;
}
