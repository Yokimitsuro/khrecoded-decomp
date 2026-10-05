#include "nitro/types.h"

typedef struct PageMenu {
    u8 pad[0x5d0];
    int cursor;
    int page;
} PageMenu;

extern u16 data_02060500;
extern BOOL IsGlobalPackedBitSet(int bit);
extern int ReadGlobalPackedBits(int bit, int width);
extern void PlaySoundEffect(int bank, int id);
extern void RefreshPageTabs(PageMenu *menu);
extern void DrawPageHeader(PageMenu *menu);

void SelectNextPage(PageMenu *menu)
{
    int oldPage = menu->page;
    int cursor = menu->cursor;
    int extra = IsGlobalPackedBitSet(cursor + 0xa01);
    int count = ReadGlobalPackedBits(cursor * 2 + 0x9f7, 2);

    if ((u32)(extra != 0) + count != 0) {
        cursor = menu->cursor;
        extra = IsGlobalPackedBitSet(cursor + 0xa01);
        count = ReadGlobalPackedBits(cursor * 2 + 0x9f7, 2);
        if (menu->page == (u32)(extra != 0) + count - 1) {
            if (data_02060500 & 0x80) {
                menu->page = 0;
            }
        } else {
            menu->page = menu->page + 1;
        }
        if (oldPage != menu->page) {
            PlaySoundEffect(0, 0);
            RefreshPageTabs(menu);
            DrawPageHeader(menu);
        }
    }
}
