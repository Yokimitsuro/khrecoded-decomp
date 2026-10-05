#include "nitro/types.h"

typedef struct OffsetTable {
    u32 primary[9];
    u32 secondary[8];
} OffsetTable;

typedef struct ArchiveState {
    u32 baseId;
    u8 pad04[0x34];
    OffsetTable *table;
} ArchiveState;

extern ArchiveState *data_020613d0;
u32 Archive_LoadFile(u32 fileId, u32 heapId, u32 unused, u32 extra);
u32 func_0202c4a0(u32 fileId, u32 heapId, u32 unused, u32 extra);

void LoadRelocatedOffsetTable(BOOL fromTop, u32 unused, u32 arg2, u32 arg3)
{
    ArchiveState *state = data_020613d0;
    u32 baseId = state->baseId;
    OffsetTable *table;
    int i;

    if (fromTop)
        state->table = (OffsetTable *)func_0202c4a0(((baseId + 0x8000) & 0xfffffc) << 7 | 0x80000005, 0x11, arg2, arg3);
    else
        state->table = (OffsetTable *)Archive_LoadFile(((baseId + 0x8000) & 0xfffffc) << 7 | 0x80000005, 0x11, arg2, arg3);

    table = state->table;
    for (i = 0; i < 9; i++)
        table->primary[i] = (u32)table + (s32)table->primary[i];
    for (i = 0; i < 8; i++)
        table->secondary[i] = (u32)table + (s32)table->secondary[i];
}
