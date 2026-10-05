#include "nitro/types.h"

typedef struct RecordEntry {
    u16 kind : 2;
    u16 variant : 3;
    u16 levelProgress : 11;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} RecordEntry;

typedef struct SaveData {
    u8 pad_0000[0x2d84];
    s16 slotHandles[16];
} SaveData;

typedef struct SlotMenu {
    u8 pad_00000[0x14];
    s32 column;
    u8 pad_00018[0x7fb8 - 0x18];
    s32 selectedCategory;
    s16 selectedRecord;
    u8 pad_07FBE[0x11ee6 - 0x7fbe];
    s16 slotIndex;
} SlotMenu;

extern SaveData *data_0205fe0c;

extern RecordEntry *GetActiveRecordEntryOrNull(int index);

static inline BOOL IsRecordHandle(u16 handle)
{
    BOOL valid = FALSE;

    if (handle >= 0x200 && handle < 0x458) {
        valid = TRUE;
    }
    return valid;
}

void SlotMenu_LoadCursorSlotRecord(SlotMenu *menu)
{
    s16 handle = data_0205fe0c->slotHandles[menu->slotIndex * 2 + menu->column];

    if (IsRecordHandle(handle)) {
        RecordEntry *record = GetActiveRecordEntryOrNull((u16)((u16)handle - 0x200));

        menu->selectedCategory = (u8)record->category;
        menu->selectedRecord = handle - 0x200;
        return;
    }
    menu->selectedCategory = handle;
    menu->selectedRecord = -1;
}
