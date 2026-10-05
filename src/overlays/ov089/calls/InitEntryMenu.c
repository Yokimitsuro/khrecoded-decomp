#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x748];
    int cursor;
} Ov089Menu;

extern int AcquireRecordSlot(int slot, int param);
extern void func_ov089_020bf0c4(void);
extern void LoadEntryModels(Ov089Menu *menu);
extern void LoadMenuBackgrounds(Ov089Menu *menu);
extern void func_ov089_020bf4bc(Ov089Menu *menu);
extern void LoadEntryMenuWidgets(Ov089Menu *menu);
extern void InitEntryUnlocks(Ov089Menu *menu);
extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern void RefreshEntryCaption(Ov089Menu *menu, BOOL playSound);
extern BOOL ShouldOpenPopupWindow(Ov089Menu *menu);
extern void OpenPopupWindow(Ov089Menu *menu);

int InitEntryMenu(Ov089Menu *menu)
{
    int row = 0;
    u32 bits;
    int col;
    BOOL found;

    AcquireRecordSlot(2, 0);
    func_ov089_020bf0c4();
    LoadEntryModels(menu);
    LoadMenuBackgrounds(menu);
    func_ov089_020bf4bc(menu);
    LoadEntryMenuWidgets(menu);
    InitEntryUnlocks(menu);
    bits = ReadSessionPackedBits(0x1e05, 0x12);
    for (; row < 6; row++) {
        found = FALSE;
        for (col = 0; col < 3; col++) {
            if (bits & (1 << (0x11 - (col + row * 3)))) {
                found = TRUE;
                break;
            }
        }
        if (!found) {
            menu->cursor = row;
            RefreshEntryCaption(menu, FALSE);
            break;
        }
    }
    if (ShouldOpenPopupWindow(menu)) {
        OpenPopupWindow(menu);
    }
    return 1;
}
