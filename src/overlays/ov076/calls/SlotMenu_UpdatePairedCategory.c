#include "nitro/types.h"

typedef struct RecordEntry {
    u16 unk_00;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} RecordEntry;

typedef struct CategoryInfo {
    u8 pad_00[0x10];
} CategoryInfo;

typedef struct SlotMenu {
    u8 pad_00000[0x14];
    s32 column;
    u8 pad_00018[0xc];
    u8 panel[0x11ec8 - 0x24];
    CategoryInfo *pairedCategory;
    u8 pad_11ecc[0x11ee6 - 0x11ecc];
    u16 slotIndex;
    u8 pad_11ee8[0x49868 - 0x11ee8];
    CategoryInfo categories[16];
} SlotMenu;

typedef struct SaveData {
    u8 pad_0000[0x2d84];
    u16 slotHandles[16];
} SaveData;

extern SaveData *data_0205fe0c;
extern RecordEntry *GetActiveRecordEntryOrNull(int index);
extern void func_ov076_020cc104(void *panel, int mode);

void SlotMenu_UpdatePairedCategory(SlotMenu *menu)
{
    u16 handle = data_0205fe0c->slotHandles[menu->slotIndex * 2 + ((u16)menu->column ^ 1)];

    if (handle >= 0x200 && handle < 0x458) {
        RecordEntry *entry = GetActiveRecordEntryOrNull((u16)(handle - 0x200));
        menu->pairedCategory = &menu->categories[(u8)entry->category];
    } else {
        menu->pairedCategory = NULL;
    }
    func_ov076_020cc104(menu->panel, menu->column == 0 ? 1 : 2);
}
