#include "nitro/types.h"

typedef struct StringTable {
    u8 header[0x28];
    u16 *strings[0x9a];
} StringTable;

typedef struct {
    u32 baseA;
    u32 baseB;
    u32 pad_08[4];
    StringTable *table;
    u8 *file;
} State;

extern State *data_020613d0;
extern u32 Archive_LoadFile(u32 fileId, u32 param2);
extern u32 func_0202c4a0(u32 fileId, u32 param2);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int alignment);
extern void MI_CpuFill8(void *dst, int value, int size);
extern void MIi_CpuCopy32(const void *src, void *dst, int size);
extern u16 *SkipWideString(u16 *text);

void LoadStringPointerTable(int useAlt)
{
    State *state = data_020613d0;
    StringTable *table;
    int i;

    if (useAlt != 0) {
        state->file = (u8 *)func_0202c4a0(((state->baseB + 0x8000) & 0xfffffc) << 7 | 0x80000002, 0x11);
        state->table = NNS_FndAllocFromDefaultExpHeapEx(sizeof(StringTable), -4);
    } else {
        state->file = (u8 *)Archive_LoadFile(((state->baseB + 0x8000) & 0xfffffc) << 7 | 0x80000002, 0x11);
        state->table = NNSi_FndAllocFromDefaultHeap(sizeof(StringTable));
    }
    table = state->table;
    MI_CpuFill8(table, 0, sizeof(StringTable));
    MIi_CpuCopy32(state->file, table, 0x28);
    table->strings[0] = (u16 *)(state->file + 0x28);
    /* Strings are packed back to back */
    for (i = 1; i < 0x9a; i++) {
        table->strings[i] = SkipWideString(table->strings[i - 1]);
    }
}
