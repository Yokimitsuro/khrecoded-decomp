#include "nitro/types.h"

typedef struct {
    u32 index;
    u8 pad_04[0x34];
    u32 nameAddress;
    u32 descriptionAddress;
} Entry;

typedef struct {
    u32 baseA;
    u32 baseB;
    u8 pad_08[0x5c];
    Entry *entries;
    u32 nameTable;
    u32 descriptionTable;
} State;

extern State *gRecordManager;
extern u32 Archive_LoadFile(u32 fileId, u32 param2);
extern u32 func_0202c4a0(u32 fileId, u32 param2);

void LoadNamedRecordTables(int useAlt)
{
    State *state = gRecordManager;
    int i;
    u32 *nameTable;
    u32 *descriptionTable;

    if (useAlt != 0) {
        state->entries = (Entry *)func_0202c4a0(((state->baseA + 0x8000) & 0xfffffc) << 7 | 0x80000009, 0x11);
        state->nameTable = func_0202c4a0(((state->baseB + 0x8000) & 0xfffffc) << 7 | 0x80000004, 0x11);
        state->descriptionTable = func_0202c4a0(((state->baseB + 0x8000) & 0xfffffc) << 7 | 0x80000006, 0x11);
    } else {
        state->entries = (Entry *)Archive_LoadFile(((state->baseA + 0x8000) & 0xfffffc) << 7 | 0x80000009, 0x11);
        state->nameTable = Archive_LoadFile(((state->baseB + 0x8000) & 0xfffffc) << 7 | 0x80000004, 0x11);
        state->descriptionTable = Archive_LoadFile(((state->baseB + 0x8000) & 0xfffffc) << 7 | 0x80000006, 0x11);
    }
    nameTable = (u32 *)state->nameTable;
    descriptionTable = (u32 *)state->descriptionTable;
    for (i = 0; i < 100; i++) {
        Entry *entry = &state->entries[i];

        entry->nameAddress = state->nameTable + nameTable[entry->index];
        entry->descriptionAddress = state->descriptionTable + descriptionTable[entry->index];
    }
}
