#include "nitro/types.h"

typedef struct SlotTable {
    u8 *records;
    int count;
    s8 *ids;
} SlotTable;

typedef struct ModelSet {
    u32 flags;
    u32 hasSub;
    u8 resource[0x214];
    SlotTable slots;
    void *sub;
    s8 bank;
} ModelSet;

typedef struct SlotIdList {
    int pad0;
    int count;
    s8 *ids;
} SlotIdList;

typedef struct SlotDesc {
    int pad0;
    int variant;
    SlotIdList *list;
} SlotDesc;

extern void AllocateObjectSlotArrays(SlotTable *table, int count, int bank);
extern u32 MakePaletteUploadParams160(int id, int variant);
extern void AcquireSharedRecordState(void *record, u32 key, void *resource, int bank);

void LoadModelSetSlots(ModelSet *set, SlotDesc *desc)
{
    SlotIdList *list = desc->list;
    SlotTable *slots = &set->slots;
    int i;
    int used;
    int id;
    u32 key;

    AllocateObjectSlotArrays(slots, list->count, set->bank + 8);
    for (i = 0, used = 0; i < list->count; i++) {
        id = list->ids[i];
        key = MakePaletteUploadParams160(id, desc->variant);
        if (key != 0) {
            AcquireSharedRecordState(slots->records + used * 0x2c, key, set->resource, set->bank + 8);
            slots->ids[used] = id;
            used++;
        }
    }
}
