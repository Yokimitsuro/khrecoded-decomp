#include "nitro/types.h"

typedef struct NameTable {
    u8 pad_00[0xa];
    u8 count;
    u8 pad_0b;
    char **names;
} NameTable;

typedef struct Session {
    u8 pad_0000[0x27e8];
    NameTable nameTable;
} Session;

extern Session *data_ov001_020a0480;
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MIi_CpuClear32(u32 value, void *destination, u32 size);

void AllocSessionNameTable(int count) {
    NameTable *table = &data_ov001_020a0480->nameTable;
    u32 size = count * 4;
    char **names;
    table->count = count;
    names = NNSi_FndAllocFromDefaultHeap(size);
    table->names = names;
    MIi_CpuClear32(0, names, size);
}
