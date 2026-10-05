#include "nitro/types.h"

typedef struct ConfigChoice {
    const void *name;
    const void *description;
} ConfigChoice;

typedef struct ConfigOption {
    u8 count;
    u8 value;
    u16 bitWidth : 2;
    u16 locked : 1;
    u16 bitIndex : 13;
    const void *label;
    ConfigChoice choices[1];
} ConfigOption;

typedef struct ConfigPage {
    u8 rowCount;
    u8 pad_01[3];
    const void *title;
    ConfigOption *options[6];
} ConfigPage;

typedef struct RowLayout {
    u8 pad_00[4];
    s16 y;
} RowLayout;

typedef struct ConfigMenu {
    u8 row;
    u8 page;
    u8 helpShown;
    u8 dirty;
    u8 pageChanged;
    u8 pad_05[3];
    void *tracker;
    void *rowTags[6];
    void *cursorTag;
    void *helpTag;
    void *headerTag;
    void *pageTabs[3];
    void *footerTag;
    void *arrowLeft;
    void *arrowRight;
    void *arrowLeftHelp;
    void *arrowRightHelp;
    ConfigPage pages[3];
    u8 objectLists[5][0x34];
    void *image;
} ConfigMenu;

extern BOOL func_ov039_020bc0f4(void);
extern void func_ov027_020b8200(void *tracker, void *tag, int y);
extern void SetTagRecordArmed(void *tracker, void *tag, BOOL arm);
extern void func_ov027_020b8230(void *tracker, void *tag);
extern void func_ov027_020b847c(void *tracker, void *tag);
extern void ConfigMenu_Refresh(ConfigMenu *menu);

void ConfigMenu_UpdateHelp(ConfigMenu *menu)
{
    BOOL idle = func_ov039_020bc0f4() == 0 ? TRUE : FALSE;

    if (idle) {
        if (menu->helpShown == 0) {
            RowLayout *layout = menu->rowTags[menu->row];
            func_ov027_020b8200(menu->tracker, menu->helpTag, layout->y);
            SetTagRecordArmed(menu->tracker, menu->cursorTag, FALSE);
            func_ov027_020b8230(menu->tracker, menu->helpTag);
            SetTagRecordArmed(menu->tracker, menu->arrowLeft, FALSE);
            func_ov027_020b8230(menu->tracker, menu->arrowLeftHelp);
            SetTagRecordArmed(menu->tracker, menu->arrowRight, FALSE);
            func_ov027_020b8230(menu->tracker, menu->arrowRightHelp);
            menu->helpShown = TRUE;
        }
    } else if (menu->helpShown != 0) {
        SetTagRecordArmed(menu->tracker, menu->cursorTag, TRUE);
        func_ov027_020b847c(menu->tracker, menu->cursorTag);
        SetTagRecordArmed(menu->tracker, menu->arrowLeft, TRUE);
        func_ov027_020b847c(menu->tracker, menu->arrowLeft);
        SetTagRecordArmed(menu->tracker, menu->arrowRight, TRUE);
        func_ov027_020b847c(menu->tracker, menu->arrowRight);
        menu->helpShown = FALSE;
    }
    ConfigMenu_Refresh(menu);
}
