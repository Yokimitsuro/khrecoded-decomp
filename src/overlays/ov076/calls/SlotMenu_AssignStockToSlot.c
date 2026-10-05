#include "nitro/types.h"

typedef struct ItemDef {
    u32 handle;
    s32 isRecord;
} ItemDef;

typedef struct ItemStock {
    u16 total;
    u16 used;
    s16 recordIndex;
    u8 pad_06[2];
    ItemDef *def;
} ItemStock;

typedef struct SlotMenu {
    u8 pad_00000[0x14];
    s32 column;
    u8 pad_00018[0x11ee6 - 0x18];
    s16 slotIndex;
} SlotMenu;

extern void *GetActiveRecordEntryOrNull(int index);
extern void func_ov076_020c8a00(SlotMenu *menu, int slot, int column);
extern void func_ov076_020c8354(SlotMenu *menu, int slot, int column, ItemStock *stock);
extern void func_ov076_020c82f8(SlotMenu *menu, int slot, int column, int recordIndex);

void SlotMenu_AssignStockToSlot(SlotMenu *menu, ItemStock *stock)
{
    int slot = menu->slotIndex;
    int column = menu->column;

    if (stock->def->isRecord == 0) {
        func_ov076_020c8a00(menu, slot, 1);
        func_ov076_020c8354(menu, slot, 0, stock);
        return;
    }
    if (column == 0) {
        GetActiveRecordEntryOrNull((u16)stock->recordIndex);
        func_ov076_020c82f8(menu, slot, 0, stock->recordIndex);
        return;
    }
    func_ov076_020c82f8(menu, slot, 1, stock->recordIndex);
}
