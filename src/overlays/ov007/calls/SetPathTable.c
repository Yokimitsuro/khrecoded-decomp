#include "nitro/types.h"

typedef struct {
    int count;
    u32 *nodes;
} PathTable;

typedef struct {
    u8 pad_00[0x88];
    PathTable *tables;
} PathSet;

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MIi_CpuCopy32(const void *src, void *dest, u32 size);

void SetPathTable(PathSet *set, int index, int count, const u32 *nodes) {
    set->tables[index].count = count;
    set->tables[index].nodes = NNSi_FndAllocFromDefaultHeap(count * 4);
    MIi_CpuCopy32(nodes, set->tables[index].nodes, count * 4);
}
