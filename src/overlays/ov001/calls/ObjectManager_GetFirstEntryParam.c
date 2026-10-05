#include "nitro/types.h"

typedef struct ParamEntry {
    u16 first;
    u16 second;
} ParamEntry;

typedef struct ParamTable {
    u32 header;
    ParamEntry entries[1];
} ParamTable;

typedef struct ObjectManager {
    u8 pad_000[0xc];
    u32 baseAddress;
    ParamTable *paramTable;
} ObjectManager;

extern ObjectManager *data_ov001_020a04f8;

u32 ObjectManager_GetFirstEntryParam(int index)
{
    return 0x80000000 | (((data_ov001_020a04f8->baseAddress + 0x8000) & 0xfffffc) << 7) |
           (data_ov001_020a04f8->paramTable->entries[index].first & 0x1ff);
}
