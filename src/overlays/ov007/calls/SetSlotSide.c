#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xa0];
    s8 slotFlags[0x10];
} SlotTable;

void SetSlotSide(SlotTable *table, int slot, BOOL first) {
    int side;

    table->slotFlags[slot] &= ~3;
    if (first) {
        side = 1;
    } else {
        side = 2;
    }
    table->slotFlags[slot] |= (s8)side;
}
