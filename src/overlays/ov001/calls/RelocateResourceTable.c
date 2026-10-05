#include "nitro/types.h"

typedef struct ResourceGroup {
    u32 unk_00;
    u32 count;
    u32 unk_08;
    u32 *offsets;
} ResourceGroup;

typedef struct ResourceTable {
    u32 unk_00;
    u32 groupCount;
    ResourceGroup *groups;
} ResourceTable;

void RelocateResourceTable(ResourceTable *table)
{
    u32 i;
    ResourceGroup *last;
    u32 *offsets;

    table->groups = (ResourceGroup *)((u32)table->groups + (u32)table);
    for (i = 0; i < table->groupCount; i++) {
        table->groups[i].offsets = (u32 *)((u8 *)table->groups[i].offsets + (u32)table);
    }
    last = &table->groups[table->groupCount - 1];
    offsets = last->offsets;
    for (i = 0; i < last->count; i++) {
        offsets[i] += (u32)table;
    }
}
