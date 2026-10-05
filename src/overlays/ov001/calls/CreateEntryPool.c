#include "nitro/types.h"

typedef struct EntryPool
{
    u8 pad_00[0x24];
    int (*callback)(void);
    u8 pad_28[0x14];
    u16 stride;
    u16 count;
    u8 *entries;
} EntryPool;

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MIi_CpuClearFast(u32 value, void *dest, u32 size);
extern int func_ov001_0208627c(void);

EntryPool *CreateEntryPool(int headerSize, int entrySize, int count)
{
    int stride = (entrySize + 3) / 4 * 4;
    int dataSize = stride * count;
    EntryPool *pool = NNSi_FndAllocFromDefaultHeap(headerSize + dataSize);

    MIi_CpuClearFast(0, pool, headerSize + dataSize);
    pool->stride = stride;
    pool->count = count;
    pool->entries = (u8 *)pool + headerSize;
    pool->callback = func_ov001_0208627c;
    return pool;
}
