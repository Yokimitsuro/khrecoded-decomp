#include "nitro/types.h"

typedef struct ConfigOption {
    u8 count;
    u8 value;
    u16 bitWidth : 2;
    u16 locked : 1;
    u16 bitIndex : 13;
} ConfigOption;

typedef struct ConfigPage {
    u8 rowCount;
    u8 pad_01[7];
    ConfigOption *options[6];
} ConfigPage;

typedef struct RowLayout {
    u8 pad_00[2];
    s16 x;
    s16 y;
} RowLayout;

typedef struct ConfigMenu {
    u8 row;
    u8 page;
    u8 pad_02;
    u8 dirty;
    u8 pageChanged;
    u8 pad_05[3];
    void *tracker;
    void *rowTags[6];
    void *cursorTag;
    u8 pad_28[4];
    void *headerTag;
    void *pageTabs[3];
    void *footerTag;
    void *arrowLeft;
    void *arrowRight;
    u8 pad_48[8];
    ConfigPage pages[3];
    u8 objectLists[5][0x34];
    void *image;
} ConfigMenu;

extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void func_ov027_020b833c(void *tracker);
extern void FreePointerIfSet(void **ptr);
extern BOOL DestroyFndObjectList(void *list);

void ConfigMenu_Release(ConfigMenu *menu)
{
    int page;
    int row;

    for (page = 2; page >= 0; page--) {
        for (row = 5; row >= 0; row--) {
            if (menu->pages[page].options[row] != NULL) {
                NNSi_FndFreeFromDefaultHeap(menu->pages[page].options[row]);
            }
        }
    }
    func_ov027_020b833c(menu->tracker);
    FreePointerIfSet(&menu->image);
    DestroyFndObjectList(menu->objectLists[0]);
    DestroyFndObjectList(menu->objectLists[1]);
    DestroyFndObjectList(menu->objectLists[2]);
    DestroyFndObjectList(menu->objectLists[3]);
    DestroyFndObjectList(menu->objectLists[4]);
}
