#include "nitro/types.h"

typedef struct {
    u32 initialized;
    void *record;
    u8 state[0x24];
} SharedRecordState;

typedef struct {
    SharedRecordState *slots;
    int count;
    s8 *ids;
} SlotArrays;

typedef struct {
    u32 state;
    u8 selection;
    u8 pad_05[0x4f];
    SlotArrays records;
} UnitResources;

extern void AllocateObjectSlotArrays(SlotArrays *arrays, int count, u32 heap);
extern u32 func_ov001_0206dba0(int index);
extern void AcquireSharedRecordState(SharedRecordState *obj, s32 key, u32 initArg, u32 context);

void InitUnitSharedRecords(UnitResources *unit, u32 initArg, int entry, s32 *ids)
{
    int i;
    SlotArrays *records = &unit->records;
    int count;
    u32 base;

    for (count = 0; ids[count] != -1; count++) {
    }
    AllocateObjectSlotArrays(records, count, unit->selection + 8);
    base = func_ov001_0206dba0(entry + 6);
    for (i = 0; i < records->count; i++) {
        AcquireSharedRecordState(&records->slots[i], ((base + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (ids[i] & 0x1ff), initArg, unit->selection + 8);
        records->ids[i] = ids[i];
    }
}
