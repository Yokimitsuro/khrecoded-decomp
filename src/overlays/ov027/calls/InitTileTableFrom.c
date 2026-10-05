#include "nitro/types.h"

typedef struct TileTable {
    int *ids;
    int count;
    u16 width;
    u16 height;
    u16 rowLength;
    u8 pad_0E[2];
    u16 *rows;
    u8 pad_14[4];
    u8 dirtyMask;
    u8 pad_19[3];
} TileTable;

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MIi_CpuClear16(u32 value, void *dst, u32 size);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);

void InitTileTableFrom(TileTable *table, const TileTable *source)
{
    int *ids;
    u16 *rows;
    int count;
    u16 width;
    u16 height;
    u32 size;

    MI_CpuFill8(table, 0, sizeof(TileTable));
    ids = NNSi_FndAllocFromDefaultHeap(source->count * sizeof(int));
    table->ids = ids;
    MI_CpuCopy8(source->ids, ids, source->count * sizeof(int));
    count = source->count;
    table->count = count;
    width = source->width;
    table->width = width;
    height = source->height;
    table->height = height;
    table->rowLength = width * height;
    size = table->rowLength * 2 * count;
    rows = NNSi_FndAllocFromDefaultHeap(size);
    table->rows = rows;
    MIi_CpuClear16(0, rows, size);
    table->dirtyMask = 0xFF;
}
