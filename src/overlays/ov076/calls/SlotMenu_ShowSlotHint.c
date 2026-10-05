#include "nitro/types.h"

typedef struct SaveData {
    u8 pad_0000[0x2d84];
    u16 slotHandles[16];
} SaveData;

typedef struct MessageTable {
    u8 data[0x10];
} MessageTable;

typedef struct SlotMenu {
    u8 pad_00000[0x14];
    s32 column;
    u8 pad_00018[0x4e80 - 0x18];
    MessageTable messages;
    u8 pad_04E90[0x11ee6 - 0x4e90];
    s16 slotIndex;
} SlotMenu;

extern SaveData *data_0205fe0c;

extern BOOL func_ov076_020c44e0(SlotMenu *menu, int slot);
extern void *func_ov027_020ba2c8(MessageTable *table, int index);
extern void func_ov076_020c8198(SlotMenu *menu, void *message);

void SlotMenu_ShowSlotHint(SlotMenu *menu)
{
    int slot = menu->slotIndex;
    int column = menu->column;
    int messageId;

    if (column == 2) {
        BOOL filled = func_ov076_020c44e0(menu, slot);

        messageId = 0x5b;
        if (!filled) {
            messageId = 0x5c;
        }
    } else if (data_0205fe0c->slotHandles[slot * 2 + column] == 0xffff) {
        messageId = 0x5c;
    } else {
        messageId = 0x26;
    }
    func_ov076_020c8198(menu, func_ov027_020ba2c8(&menu->messages, messageId));
}
