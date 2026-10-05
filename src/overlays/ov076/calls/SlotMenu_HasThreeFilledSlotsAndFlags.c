#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00000[0x49818];
    u16 slotPoints[8];
} SlotMenu;

typedef struct SaveData {
    u8 pad_0000[0x2c68];
    u8 extraSlotCount;
} SaveData;

extern SaveData *data_0205fe0c;
extern BOOL IsGlobalPackedBitSet(int bitIndex);

BOOL SlotMenu_HasThreeFilledSlotsAndFlags(SlotMenu *menu)
{
    int slotCount = data_0205fe0c->extraSlotCount + 3;
    int slot = 0;
    int filledCount = 0;

    for (; slot < slotCount; slot++) {
        if (menu->slotPoints[slot] != 0 && ++filledCount == 3) {
            if (IsGlobalPackedBitSet(0xf74) && IsGlobalPackedBitSet(0xf75) &&
                IsGlobalPackedBitSet(0xf7a) && IsGlobalPackedBitSet(0xf78) &&
                IsGlobalPackedBitSet(0xf79) && IsGlobalPackedBitSet(0xf7d)) {
                return TRUE;
            }
            return FALSE;
        }
    }
    return FALSE;
}
