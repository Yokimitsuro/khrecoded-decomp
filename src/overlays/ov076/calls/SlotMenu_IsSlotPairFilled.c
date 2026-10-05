#include "nitro/types.h"

typedef struct SaveData {
    u8 pad_0000[0x2d84];
    u16 slotHandles[16];
} SaveData;

extern SaveData *data_0205fe0c;

BOOL SlotMenu_IsSlotPairFilled(void *menu, int slot)
{
    int pairIndex = slot * 2;
    u16 first = data_0205fe0c->slotHandles[pairIndex];
    u16 second = data_0205fe0c->slotHandles[pairIndex + 1];

    if (first >= 0x200 && first < 0x458 && second >= 0x200 && second < 0x458) {
        return TRUE;
    }
    return FALSE;
}
