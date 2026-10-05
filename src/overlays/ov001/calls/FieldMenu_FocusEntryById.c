#include "nitro/types.h"

typedef struct MenuEntry {
    u32 unk_00;
    s32 defaultFrame;
    u32 unk_08;
    s32 id;
    u8 pad_10[0x18];
    u16 flags;
    s16 frame;
    u8 pad_2c[0x10];
} MenuEntry;

typedef struct FieldMenu {
    u8 pad_000[0xac];
    MenuEntry *entries;
    u8 pad_0b0[0x14];
    s32 entryTotal;
    s32 focusActive;
    u8 pad_0cc[0x20];
    s32 entryIndex;
} FieldMenu;

typedef struct FieldMenuHandle {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04d0;
extern MenuEntry *CycleMenuEntry(FieldMenu *menu, s32 index, s32 slot, s32 *outValue);
extern void func_ov001_020769f4(FieldMenu *menu);

void FieldMenu_FocusEntryById(int id)
{
    FieldMenu *menu = data_ov001_020a04d0.menu;
    int i;

    if (id == -1) {
        if (menu->focusActive > 0) {
            CycleMenuEntry(menu, menu->entryIndex, 1, NULL)->frame = 0;
            menu->focusActive = 0;
            func_ov001_020769f4(menu);
        }
        return;
    }
    for (i = 0; i < menu->entryTotal; i++) {
        MenuEntry *entry = &menu->entries[i];
        if (entry->id == id) {
            menu->focusActive = 1;
            menu->entries[menu->entryIndex].frame = 0;
            menu->entryIndex = i;
            entry->frame = entry->defaultFrame;
            entry->flags |= 2;
            return;
        }
    }
}
