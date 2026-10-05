#include "nitro/types.h"

typedef struct SubModel {
    u8 resource[0x104];
    u8 slots[0xc];
} SubModel;

typedef struct ModelSet {
    u32 flags;
    u32 field4;
    u8 resource[0x104];
    int field10c;
    u8 pad110[4];
    u8 records[6][0x2c];
    u8 slots[0xc];
    SubModel *sub;
} ModelSet;

extern void ReleaseSharedRecordState(void *record);
extern void FreeSlotTable(void *table);
extern void ReleaseResourceAndDetach(void *resource);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void ReleaseModelSet(ModelSet *set)
{
    int i;
    SubModel *sub;

    if (!(set->flags & 1)) {
        return;
    }
    for (i = 0; i < 6; i++) {
        ReleaseSharedRecordState(set->records[i]);
    }
    FreeSlotTable(set->slots);
    ReleaseResourceAndDetach(set->resource);
    sub = set->sub;
    if (sub != NULL) {
        FreeSlotTable(sub->slots);
        ReleaseResourceAndDetach(sub);
        NNSi_FndFreeFromDefaultHeap(set->sub);
    }
    set->field10c = 0;
    set->flags = 0;
}
