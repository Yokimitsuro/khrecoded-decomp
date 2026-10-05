#include "nitro/types.h"

typedef struct {
    u32 index;
    u32 pad[4];
    u32 address;
} Entry;

typedef struct {
    u32 baseA;
    u32 baseB;
    u32 pad[19];
    Entry *entries;
    u32 table;
} State;

extern State *data_020613d0;
extern u32 Archive_LoadFile(u32 fileId, u32 param2);
extern u32 func_0202c4a0(u32 fileId, u32 param2);

void LoadRecordTables(int useAlt)
{
    State *state = data_020613d0;
    int i;
    u32 *table;

    if (useAlt != 0) {
        state->entries = (Entry *)func_0202c4a0(((state->baseA + 0x8000) & 0xfffffc) << 7 | 0x80000008, 0x11);
        state->table = func_0202c4a0(((state->baseB + 0x8000) & 0xfffffc) << 7 | 0x80000003, 0x11);
    } else {
        state->entries = (Entry *)Archive_LoadFile(((state->baseA + 0x8000) & 0xfffffc) << 7 | 0x80000008, 0x11);
        state->table = Archive_LoadFile(((state->baseB + 0x8000) & 0xfffffc) << 7 | 0x80000003, 0x11);
    }
    table = (u32 *)state->table;
    for (i = 0; i < 0x5a1; i++) {
        state->entries[i].address = state->table + table[state->entries[i].index];
    }
}
