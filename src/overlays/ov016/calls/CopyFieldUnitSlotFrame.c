#include "nitro/types.h"

typedef struct {
    u8 data[0x1e0];
} SlotFrame;

typedef struct {
    u8 pad_00[0xc4];
    void *slotRecords;
} FieldUnit;

typedef struct {
    u8 pad_00[4];
    FieldUnit *unit;
} FieldLink;

extern SlotFrame *GetFieldUnitSlotRecord(FieldUnit *unit, void *records);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);

void CopyFieldUnitSlotFrame(FieldLink *link, int index, void *dest)
{
    MIi_CpuCopyFast(&GetFieldUnitSlotRecord(link->unit, link->unit->slotRecords)[index], dest,
                             sizeof(SlotFrame));
}
