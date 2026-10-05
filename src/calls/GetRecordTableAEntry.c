#include "nitro/types.h"

typedef struct RecordTableAEntry {
    u8 data[0x10];
} RecordTableAEntry;

typedef struct RecordTableA {
    u8 header[0x14];
    RecordTableAEntry entries[];
} RecordTableA;

typedef struct RecordManager {
    u8 pad_00[0x40];
    RecordTableA *tableA;
} RecordManager;

extern RecordManager *gRecordManager;

RecordTableAEntry *GetRecordTableAEntry(u32 index)
{
    return &gRecordManager->tableA->entries[index];
}
