#include "nitro/types.h"

typedef struct ItemMenu {
    u8 pad_0000[0x18];
    void *objManager;
    u8 pad_001c[4];
    u16 tab;
    u8 pad_0022[0x4d78 - 0x22];
    u16 itemCount;
    u8 pad_4d7a[0x4d84 - 0x4d7a];
    u16 visibleCount;
    s16 selected;
    s16 scrollTop;
} ItemMenu;

extern u16 BuildTabItemList(ItemMenu *menu, int tab);
extern void PlaySoundEffect(int channel, int id);
extern int FindWidgetById(void *manager, int elementId);
extern void func_ov027_020b96c0(void *manager, int element, u16 frame);
extern void func_ov075_020cdfa8(ItemMenu *menu);

BOOL SelectItemTab(ItemMenu *menu, int tab)
{
    BOOL changed;

    if ((menu->tab != tab && BuildTabItemList(menu, tab) != 0) || tab == 1) {
        changed = TRUE;
    } else {
        changed = FALSE;
    }
    if (changed) {
        PlaySoundEffect(1, 2);
        menu->tab = tab;
        menu->visibleCount = menu->itemCount;
        menu->selected = 0;
        menu->scrollTop = menu->selected;
        func_ov027_020b96c0(menu->objManager, FindWidgetById(menu->objManager, 0x1b), tab);
        func_ov075_020cdfa8(menu);
    } else {
        PlaySoundEffect(1, 4);
    }
    return changed;
}