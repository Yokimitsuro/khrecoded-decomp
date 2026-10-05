#include "nitro/types.h"

typedef struct PageMenu {
    u8 pad[0x24];
    void *nodes[11];
    u8 pad50[0x5d0 - 0x50];
    int cursor;
    int page;
} PageMenu;

extern void *func_ov039_020bc1dc(void);
extern BOOL IsGlobalPackedBitSet(int bit);
extern int ReadGlobalPackedBits(int bit, int width);
extern void SetEntrySlotsVisible(void *scene, void *node, BOOL visible);

void ShowUnlockedPageTabs(PageMenu *menu)
{
    void *scene = func_ov039_020bc1dc();
    int cursor = menu->cursor;
    int extra = IsGlobalPackedBitSet(cursor + 0xa01);
    int count = ReadGlobalPackedBits(cursor * 2 + 0x9f7, 2);

    switch ((u32)(extra != 0) + count) {
    case 0:
    case 1:
        SetEntrySlotsVisible(scene, menu->nodes[2], FALSE);
        SetEntrySlotsVisible(scene, menu->nodes[3], FALSE);
        SetEntrySlotsVisible(scene, menu->nodes[4], FALSE);
        SetEntrySlotsVisible(scene, menu->nodes[5], TRUE);
        SetEntrySlotsVisible(scene, menu->nodes[6], FALSE);
        SetEntrySlotsVisible(scene, menu->nodes[7], FALSE);
        break;
    case 2:
        SetEntrySlotsVisible(scene, menu->nodes[2], FALSE);
        SetEntrySlotsVisible(scene, menu->nodes[3], TRUE);
        SetEntrySlotsVisible(scene, menu->nodes[4], FALSE);
        SetEntrySlotsVisible(scene, menu->nodes[5], TRUE);
        SetEntrySlotsVisible(scene, menu->nodes[6], FALSE);
        SetEntrySlotsVisible(scene, menu->nodes[7], FALSE);
        break;
    case 3:
        SetEntrySlotsVisible(scene, menu->nodes[2], FALSE);
        SetEntrySlotsVisible(scene, menu->nodes[3], TRUE);
        SetEntrySlotsVisible(scene, menu->nodes[4], TRUE);
        SetEntrySlotsVisible(scene, menu->nodes[5], TRUE);
        SetEntrySlotsVisible(scene, menu->nodes[6], FALSE);
        SetEntrySlotsVisible(scene, menu->nodes[7], FALSE);
        break;
    }

    switch (ReadGlobalPackedBits(menu->cursor * 2 + 0x9f7, 2)) {
    case 0:
        SetEntrySlotsVisible(scene, menu->nodes[8], FALSE);
        SetEntrySlotsVisible(scene, menu->nodes[9], FALSE);
        SetEntrySlotsVisible(scene, menu->nodes[10], FALSE);
        break;
    case 1:
        SetEntrySlotsVisible(scene, menu->nodes[8], TRUE);
        SetEntrySlotsVisible(scene, menu->nodes[9], FALSE);
        SetEntrySlotsVisible(scene, menu->nodes[10], FALSE);
        break;
    case 2:
        SetEntrySlotsVisible(scene, menu->nodes[8], TRUE);
        SetEntrySlotsVisible(scene, menu->nodes[9], TRUE);
        SetEntrySlotsVisible(scene, menu->nodes[10], FALSE);
        break;
    case 3:
        SetEntrySlotsVisible(scene, menu->nodes[8], TRUE);
        SetEntrySlotsVisible(scene, menu->nodes[9], TRUE);
        SetEntrySlotsVisible(scene, menu->nodes[10], TRUE);
        break;
    }
}
