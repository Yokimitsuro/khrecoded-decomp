#include "nitro/types.h"

typedef struct RecordEntry {
    u16 kind : 2;
    u16 rank : 3;
    u16 levelProgress : 11;
} RecordEntry;

typedef struct SaveData {
    u8 pad_0000[0x2c68];
    u8 extraSlotCount;
    u8 pad_2C69[0x2d84 - 0x2c69];
    u16 slotHandles[16];
} SaveData;

typedef struct SlotMenu {
    u8 pad_00000[0x4a078];
    u32 slotMasks[3];
} SlotMenu;

extern SaveData *data_0205fe0c;
extern RecordEntry *GetActiveRecordEntryOrNull(int index);

static inline BOOL IsHandleValid(u32 handle)
{
    BOOL valid = FALSE;
    if (handle >= 0x200 && handle < 0x458) {
        valid = TRUE;
    }
    return valid;
}

void SlotMenu_BuildSlotMasks(SlotMenu *menu, int mode, BOOL checkRank)
{
    int slotCount = data_0205fe0c->extraSlotCount + 3;
    int slot;
    u32 mask = 0;

    menu->slotMasks[2] = 0;
    menu->slotMasks[1] = 0;
    menu->slotMasks[0] = 0;
    if (mode < 0) {
        return;
    }
    for (slot = 0; slot < slotCount; slot++) {
        int pairIndex = slot * 2;
        u16 first = data_0205fe0c->slotHandles[pairIndex];
        u16 second = data_0205fe0c->slotHandles[pairIndex + 1];

        if (mode == 0) {
            if (first == 0xffff) {
                mask |= 1 << (slot * 3);
            } else if (second == 0xffff) {
                mask |= 1 << (slot * 3 + 1);
            }
        }
        if (mode == 1 && first != 0xffff && second == 0xffff) {
            mask |= 1 << (slot * 3 + 1);
        }
        if (mode == 2 || checkRank) {
            BOOL ranked = FALSE;
            if (IsHandleValid(first) && GetActiveRecordEntryOrNull((u16)(first - 0x200))->rank != 0) {
                ranked = TRUE;
            }
            if (ranked) {
                ranked = FALSE;
                if (IsHandleValid(second) && GetActiveRecordEntryOrNull((u16)(second - 0x200))->rank != 0) {
                    ranked = TRUE;
                }
                if (ranked) {
                    mask |= 1 << (slot * 3 + 2);
                }
            }
        }
    }
    menu->slotMasks[mode] = mask;
}
