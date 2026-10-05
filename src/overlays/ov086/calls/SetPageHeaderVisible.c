#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x134];
    int pageIndex;
    u8 pad_138[4];
    int stepCount;
    int itemId;
} Ov086Menu;

extern u8 *func_ov039_020bc1ec(void);
extern void *FindWidgetById(u8 *panel, int elementId);
extern void SetEntrySlotsVisible(u8 *panel, void *element, BOOL visible);
extern void DrawRecordHintText(Ov086Menu *menu);

void SetPageHeaderVisible(Ov086Menu *menu, BOOL visible)
{
    u8 *panel = func_ov039_020bc1ec();
    void *element;

    if (menu->pageIndex == 3) {
        element = FindWidgetById(panel, 0xd);
    } else if (menu->pageIndex == 6) {
        element = FindWidgetById(panel, 0x10);
    } else {
        element = FindWidgetById(panel, 0xb);
    }
    SetEntrySlotsVisible(panel, element, visible);
    if (menu->pageIndex != 7 && ((menu->pageIndex == 6 && menu->stepCount == 1) || (menu->pageIndex != 6 && menu->stepCount >= 1))) {
        if (menu->itemId != 0) {
            SetEntrySlotsVisible(panel, FindWidgetById(panel, 0x2d), visible);
        }
        if (menu->itemId != 0x38) {
            SetEntrySlotsVisible(panel, FindWidgetById(panel, 0x2e), visible);
        }
    }
    DrawRecordHintText(menu);
}
