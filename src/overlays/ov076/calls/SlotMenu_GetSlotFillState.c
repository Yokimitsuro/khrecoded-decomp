#include "nitro/types.h"

typedef struct SaveData {
    u8 pad_0000[0x2d84];
    u16 slotHandles[16];
} SaveData;

extern SaveData *data_0205fe0c;

int SlotMenu_GetSlotFillState(int slot, int position)
{
    position -= 8;
    if (position < 0) {
        return -3;
    }
    switch (position / 16) {
    case 0:
        return 0;
    case 1: {
        u16 handle = data_0205fe0c->slotHandles[slot * 2];
        if (handle >= 0x200 && handle < 0x458) {
            return 1;
        }
        return -1;
    }
    case 2: {
        int pairIndex = slot * 2;
        BOOL filled = FALSE;
        u16 first = data_0205fe0c->slotHandles[pairIndex];
        if (first >= 0x200 && first < 0x458) {
            u16 second = data_0205fe0c->slotHandles[pairIndex + 1];
            if (second >= 0x200 && second < 0x458) {
                filled = TRUE;
            }
        }
        if (filled) {
            return 2;
        }
        return -2;
    }
    }
    return -3;
}
