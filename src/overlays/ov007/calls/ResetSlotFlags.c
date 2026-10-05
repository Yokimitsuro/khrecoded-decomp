#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x8c];
    u32 slotCount;
    u8 slotModes[0x10];
    u8 slotFlags[0x10];
} SlotTable;

extern void MI_CpuFill8(void *dest, u8 data, u32 size);

void ResetSlotFlags(SlotTable *table, u32 count) {
    table->slotCount = count;
    MI_CpuFill8(table->slotModes, 0x1f, count);
    MI_CpuFill8(table->slotFlags, 0, count);
}
