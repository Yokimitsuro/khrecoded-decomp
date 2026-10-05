#include "nitro/types.h"

typedef struct RecordEntry {
    u16 kind : 2;
    u16 unk_00_2 : 3;
    u16 levelProgress : 11;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} RecordEntry;

typedef struct SlotItem {
    u8 pad_00[0x10];
    s32 visible;
    u8 pad_14[4];
} SlotItem;

typedef struct SlotView {
    u8 pad_000[0x10];
    SlotItem items[17];
    u8 pad_1A8[8];
} SlotView;

typedef struct SlotMenu {
    u8 pad_00000[0x1b914];
    SlotView slots[8];
    u8 pad_1C694[0x497f8 - 0x1c694];
    RecordEntry records[8];
    u16 iconIds[8];
} SlotMenu;

typedef struct SaveData {
    u8 pad_0000[0x2d84];
    u16 slotHandles[16];
} SaveData;

typedef struct SlotPair0Entry {
    u8 pad_00[0x20];
    int pair1Index;
} SlotPair0Entry;

typedef struct SlotPair1Entry {
    u8 pad_00[0x1e];
    u16 iconId;
} SlotPair1Entry;

extern SaveData *data_0205fe0c;

extern RecordEntry *GetActiveRecordEntryOrNull(int index);
extern BOOL ResolveMergedRecordEntry(int index, RecordEntry *entry, u32 *outValue);
extern SlotPair0Entry *GetRecordSlotPair0Entry(s32 index);
extern SlotPair1Entry *GetRecordSlotPair1Entry(s32 index);
extern int GetSharedSelectedIndex(void);
extern void func_ov073_020c1ed4(SaveData *save, int arg);
extern void func_ov076_020c6d4c(SlotMenu *menu, int slot, RecordEntry *record, int mode);
extern void func_ov076_020c6e58(SlotMenu *menu, int slot, RecordEntry *record, int mode);
extern void SlotMenu_DrawEmptyLabel(SlotMenu *menu, int slot, int part);
extern void func_ov076_020c7c40(SlotMenu *menu, int slot, int part, RecordEntry *entry);
extern void func_ov076_020c7efc(SlotMenu *menu, int slot, int part, int handle);

void SlotMenu_ReloadSlot(SlotMenu *menu, int slot, int mode)
{
    SlotView *view = &menu->slots[slot];
    int pairIndex;
    RecordEntry *entry;
    SlotPair0Entry *pair0;
    u16 handle;
    u16 secondHandle;
    u32 mergedValue;

    menu->records[slot].active = 0;
    pairIndex = slot * 2;
    menu->iconIds[slot] = 0;
    view->items[0].visible = 0;
    view->items[1].visible = 0;
    view->items[2].visible = 0;
    view->items[3].visible = 0;
    view->items[5].visible = 0;
    view->items[4].visible = 0;
    view->items[6].visible = 0;
    view->items[7].visible = 0;
    view->items[8].visible = 0;
    view->items[9].visible = 0;
    view->items[11].visible = 0;
    view->items[10].visible = 0;
    view->items[12].visible = 0;
    view->items[13].visible = 0;
    view->items[14].visible = 0;
    view->items[15].visible = 0;
    view->items[16].visible = 0;

    handle = data_0205fe0c->slotHandles[pairIndex];
    if (handle != 0xffff) {
        if (handle >= 0x200 && handle < 0x458) {
            RecordEntry *first = GetActiveRecordEntryOrNull((u16)(handle - 0x200));
            entry = &menu->records[slot];
            func_ov076_020c6d4c(menu, slot, first, mode);
            ResolveMergedRecordEntry(slot, entry, &mergedValue);
            secondHandle = data_0205fe0c->slotHandles[pairIndex + 1];
            if (secondHandle != 0xffff) {
                RecordEntry *second = GetActiveRecordEntryOrNull((u16)(secondHandle - 0x200));
                func_ov076_020c6e58(menu, slot, second, mode);
                if (entry->level == 100) {
                    menu->slots[slot].items[14].visible = 1;
                }
                func_ov076_020c7c40(menu, slot, 2, entry);
            } else {
                SlotMenu_DrawEmptyLabel(menu, slot, 1);
                SlotMenu_DrawEmptyLabel(menu, slot, 2);
            }
            pair0 = GetRecordSlotPair0Entry((u8)entry->category);
            menu->iconIds[slot] = GetRecordSlotPair1Entry(pair0->pair1Index)->iconId;
        } else {
            func_ov076_020c7efc(menu, slot, 0, handle);
            SlotMenu_DrawEmptyLabel(menu, slot, 1);
            SlotMenu_DrawEmptyLabel(menu, slot, 2);
            pair0 = GetRecordSlotPair0Entry(handle);
            menu->iconIds[slot] = GetRecordSlotPair1Entry(pair0->pair1Index)->iconId;
        }
    } else {
        SlotMenu_DrawEmptyLabel(menu, slot, 0);
        SlotMenu_DrawEmptyLabel(menu, slot, 1);
        SlotMenu_DrawEmptyLabel(menu, slot, 2);
    }
    if (GetSharedSelectedIndex() != 4) {
        func_ov073_020c1ed4(data_0205fe0c, 0);
    }
}
