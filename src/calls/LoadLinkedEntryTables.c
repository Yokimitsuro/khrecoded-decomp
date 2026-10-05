#include "nitro/types.h"

typedef struct {
    u32 index;
    u32 pad[11];
    u32 address;
} LinkedEntry;

typedef struct {
    u32 baseA;
    u32 baseB;
    u32 pad[21];
    LinkedEntry *entries;
    u32 table;
} TableState;

extern TableState *gRecordManager;
extern u32 Archive_LoadFile(u32 fileId, u32 param2);
extern u32 func_0202c4a0(u32 fileId, u32 param2);

void LoadLinkedEntryTables(int useAlt)
{
    TableState *TableState = gRecordManager;
    int i;
    u32 *table;

    if (useAlt != 0) {
        TableState->entries = (LinkedEntry *)func_0202c4a0(((TableState->baseA + 0x8000) & 0xfffffc) << 7 | 0x8000000a, 0x11);
        TableState->table = func_0202c4a0(((TableState->baseB + 0x8000) & 0xfffffc) << 7 | 0x80000005, 0x11);
    } else {
        TableState->entries = (LinkedEntry *)Archive_LoadFile(((TableState->baseA + 0x8000) & 0xfffffc) << 7 | 0x8000000a, 0x11);
        TableState->table = Archive_LoadFile(((TableState->baseB + 0x8000) & 0xfffffc) << 7 | 0x80000005, 0x11);
    }
    table = (u32 *)TableState->table;
    for (i = 0; i < 0x5d; i++) {
        TableState->entries[i].address = TableState->table + table[TableState->entries[i].index];
    }
}
