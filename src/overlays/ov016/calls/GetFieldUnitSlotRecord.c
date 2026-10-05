#include "nitro/types.h"

typedef struct {
    u8 data[0xc4];
} SlotRecord;

typedef struct {
    u8 pad_00[0x3e];
    u16 slotIndex;
    u8 pad_40[0xc8 - 0x40];
    u16 slotCount : 5;
    u16 slotFlags : 11;
} FieldUnit;

SlotRecord *GetFieldUnitSlotRecord(FieldUnit *unit, SlotRecord *records)
{
    if (unit->slotCount == 0) {
        return NULL;
    }
    return &records[unit->slotIndex];
}
