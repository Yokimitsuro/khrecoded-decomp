#include "nitro/types.h"

typedef struct SlotMenu {
    s32 state;
    u8 pad_00004[0x14 - 4];
    s32 column;
    u8 pad_00018[0x24 - 0x18];
    u8 touchInput[4];
    BOOL columnLocked;
    u8 pad_0002C[0x11ee6 - 0x2c];
    s16 slotIndex;
} SlotMenu;

typedef BOOL (*SlotMenuCheck)(SlotMenu *menu);
typedef void (*SlotMenuAction)(SlotMenu *menu);

typedef struct SaveData {
    u8 pad_0000[0x2d84];
    u16 slotHandles[16];
} SaveData;

extern SaveData *data_0205fe0c;
extern char data_ov076_020cd280[];

extern void *GetActiveRecordEntryOrNull(int index);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void SlotMenu_UnequipSlotEntry(SlotMenu *menu, int slot, int column);
extern void SlotMenu_ReloadSlot(SlotMenu *menu, int slot, int mode);
extern void SlotMenu_CheckPointLimit(SlotMenu *menu, int mode);
extern void SlotMenu_ShowSlotHint(SlotMenu *menu);
extern void SlotMenu_SelectGuideStep(SlotMenu *menu);
extern BOOL func_ov076_020cbbc0(void *touch, SlotMenu *menu, SlotMenuCheck check, SlotMenuAction action, void *region, int arg5);
extern BOOL SlotMenu_OpenEmptySlot(SlotMenu *menu);
extern void SlotMenu_BeginSlotSelection(SlotMenu *menu);
extern void *func_ov039_020bc1dc(void);
extern void SetNavigationElementsVisible(void *container, BOOL visible);

void SlotMenu_UnequipCursorSlot(SlotMenu *menu)
{
    int column = menu->column;
    int slot = menu->slotIndex;
    u16 handle;

    if (menu->columnLocked == FALSE && menu->state == 1 && column != 2) {
        handle = data_0205fe0c->slotHandles[slot * 2 + column];
        if (handle != 0xffff) {
            if (handle < 0x200) {
                PlaySoundEffect(1, 6);
                SlotMenu_UnequipSlotEntry(menu, slot, column);
                SlotMenu_ReloadSlot(menu, slot, 0);
                SlotMenu_CheckPointLimit(menu, 0);
                SlotMenu_ShowSlotHint(menu);
                return;
            }
            GetActiveRecordEntryOrNull((u16)(handle - 0x200));
            PlaySoundEffect(1, 6);
            if (column == 0) {
                SlotMenu_UnequipSlotEntry(menu, slot, 1);
            }
            SlotMenu_UnequipSlotEntry(menu, slot, column);
            SlotMenu_ReloadSlot(menu, slot, 0);
            SlotMenu_CheckPointLimit(menu, 0);
            SlotMenu_ShowSlotHint(menu);
            SlotMenu_SelectGuideStep(menu);
            if (func_ov076_020cbbc0(menu->touchInput, menu, SlotMenu_OpenEmptySlot, SlotMenu_BeginSlotSelection, data_ov076_020cd280, 1)) {
                menu->state = 2;
                SetNavigationElementsVisible(func_ov039_020bc1dc(), FALSE);
            }
        }
    }
}
