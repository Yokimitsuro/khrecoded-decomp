#include "nitro/types.h"

typedef struct ItemDef {
    u32 handle;
    u8 pad_04[0x1c];
    u32 reward;
} ItemDef;

typedef struct ItemStock {
    u16 total;
    u16 used;
    u8 pad_04[4];
    ItemDef *def;
} ItemStock;

typedef struct ItemListMenu {
    u8 pad_0000[0xc];
    u8 locked;
    u8 pad_000D[0x3c18 - 0xd];
    ItemStock *stocks[(0x4d86 - 0x3c18) / 4];
    u8 pad_4D84[2];
    s16 cursorIndex;
    u8 pad_4D88[0x7f9c - 0x4d88];
    s32 state;
} ItemListMenu;

typedef struct SaveData {
    u8 pad_0000[0x2c68];
    u8 extraSlotCount;
    u8 pad_2C69[0x2d84 - 0x2c69];
    u16 slotHandles[30];
    s32 slotStock[16];
} SaveData;

extern SaveData *data_0205fe0c;

extern void func_ov076_020ca644(u32 reward);
extern void DecrementByteCounter(u32 index);
extern u16 GetByteCounterOrDefault(u32 index);
extern void func_ov073_020c1ed4(SaveData *save, int mode);
extern BOOL func_ov076_020ca918(ItemListMenu *menu);

void ItemList_ReturnCursorItem(ItemListMenu *menu)
{
    u16 handle;
    ItemStock *stock;

    if (!menu->locked) {
        stock = menu->stocks[menu->cursorIndex];
        func_ov076_020ca644(stock->def->reward);
        if (stock->total > stock->used) {
            DecrementByteCounter(stock->def->handle);
            stock->total = GetByteCounterOrDefault(stock->def->handle);
        } else {
            SaveData *save;
            int slot;

            handle = stock->def->handle;
            DecrementByteCounter(handle);
            save = data_0205fe0c;
            for (slot = save->extraSlotCount + 3; slot >= 0; slot--) {
                u16 slotHandle = save->slotHandles[slot * 2];
                if (slotHandle < 0x200 && slotHandle == handle && save->slotStock[slot] != 0) {
                    break;
                }
            }
            save->slotStock[slot]--;
            stock->total--;
            stock->used--;
        }
        func_ov073_020c1ed4(data_0205fe0c, 0);
    }
    menu->state = 4;
    func_ov076_020ca918(menu);
}
