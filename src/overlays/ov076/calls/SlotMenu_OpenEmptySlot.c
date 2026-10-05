#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00000[0x49818];
    u16 slotPoints[8];
} SlotMenu;

typedef struct SaveData {
    u8 pad_0000[0x2c68];
    u8 extraSlotCount;
    u8 pad_2C69[0x2d84 - 0x2c69];
    u16 slotHandles[16];
} SaveData;

extern SaveData *data_0205fe0c;
extern char data_ov076_020cd280[];
extern int GetPrimaryRecordCount(void);
extern void func_ov076_020c5318(SlotMenu *menu, u16 slot, int arg2, int arg3, void *arg4);

static inline BOOL IsHandleValid(u32 handle)
{
    return handle >= 0x200 && handle < 0x458;
}

BOOL SlotMenu_OpenEmptySlot(SlotMenu *menu)
{
    SaveData *save;
    int slotCount;
    int emptySlot;
    int slot;
    int filledCount;

    save = data_0205fe0c;
    slotCount = save->extraSlotCount + 3;
    emptySlot = 0;

    for (slot = 0; slot < slotCount; slot++) {
        if (menu->slotPoints[slot] == 0) {
            emptySlot = slot;
            break;
        }
    }
    if (slot < slotCount) {
        filledCount = 0;
        for (slot = 0; slot < slotCount; slot++) {
            filledCount += IsHandleValid(save->slotHandles[slot * 2]) ? 1 : 0;
            filledCount += IsHandleValid(save->slotHandles[slot * 2 + 1]) ? 1 : 0;
        }
        if (filledCount < GetPrimaryRecordCount()) {
            func_ov076_020c5318(menu, emptySlot, 0, 0, data_ov076_020cd280);
            return TRUE;
        }
    }
    return FALSE;
}
