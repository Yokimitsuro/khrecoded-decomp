#include "nitro/types.h"

typedef struct TabMenu {
    u8 mode;
    u8 dirty;
    u8 pad2;
    s8 tab;
    u8 pad4[8];
    int hasExtraTab;
} TabMenu;

extern s8 data_ov085_020c22e4[];
extern void PlaySoundEffect(int channel, int id);
extern BOOL FilterItemsForTab(TabMenu *menu, int category);
extern void MoveTabCursor(TabMenu *menu, int tab);
extern void func_ov085_020c1570(TabMenu *menu);

void SelectPrevTab(TabMenu *menu)
{
    int step = 1;
    s16 last;
    s16 tab;

    if (menu->hasExtraTab == 0) {
        step = 2;
    }
    last = 5 - step;
    if (menu->mode == 0) {
        tab = menu->tab;
        do {
            tab--;
            if (tab < 0) {
                tab = last;
            }
        } while (menu->tab != tab && !FilterItemsForTab(menu, data_ov085_020c22e4[tab]));
        if (menu->tab != tab) {
            PlaySoundEffect(0, 2);
        }
        menu->tab = tab;
        MoveTabCursor(menu, menu->tab);
        func_ov085_020c1570(menu);
        menu->dirty = 1;
    }
}
