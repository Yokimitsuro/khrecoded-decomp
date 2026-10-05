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

extern void func_ov027_020b8514(void *tracker, void *tag, s16 x, s16 y);
extern void func_ov027_020b847c(void *tracker, void *tag);
extern void func_ov027_020b8230(void *tracker, void *tag);
extern void SetTagRecordArmed(void *tracker, void *tag, BOOL arm);

void ConfigMenu_UpdateTags(ConfigMenu *menu)
{
    ConfigPage *pages = menu->pages;
    int page = menu->page;
    int i;

    for (i = 0; i < pages[page].rowCount; i++) {
        if (i == menu->row) {
            RowLayout *layout = menu->rowTags[0];
            func_ov027_020b8514(menu->tracker, menu->cursorTag, layout->x, layout->y + i * 2);
            func_ov027_020b847c(menu->tracker, menu->cursorTag);
        } else {
            func_ov027_020b8230(menu->tracker, menu->rowTags[i]);
        }
    }
    if (menu->pageChanged) {
        func_ov027_020b8230(menu->tracker, menu->headerTag);
        for (i = 0; i < 3; i++) {
            BOOL selected = TRUE;
            if (i != menu->page) {
                selected = FALSE;
            }
            SetTagRecordArmed(menu->tracker, menu->pageTabs[i], selected);
            if (selected) {
                func_ov027_020b847c(menu->tracker, menu->pageTabs[i]);
            }
        }
        func_ov027_020b8230(menu->tracker, menu->footerTag);
        func_ov027_020b847c(menu->tracker, menu->arrowLeft);
        func_ov027_020b847c(menu->tracker, menu->arrowRight);
    }
}
