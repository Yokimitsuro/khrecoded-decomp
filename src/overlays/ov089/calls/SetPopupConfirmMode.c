#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x7ec];
    u8 promptLayer[0x34];
    u8 yesLayer[0x34];
    u8 noLayer[0x34];
    u8 pad_888[0x74];
    BOOL confirmMode;
} Ov089Menu;

extern void *func_ov039_020bc1dc(void);
extern u16 *UpdateScreenWidgetLayer(int screen);
extern void *FindWidgetById(void *container, int id);
extern void SetEntrySlotsVisible(void *container, void *widget, BOOL visible);
extern void CallStateWidget(int a, int b, int c, int d, int e);
extern void FillBackgroundLayerRect(void *layer, u16 *dst, int x, int y, u8 palette);
extern void SetFocusedWidget(void *container, void *widget);
extern void *func_ov039_020bc638(void);
extern void MoveCursorToElement(void *menu, void *element, BOOL playSound);

void SetPopupConfirmMode(Ov089Menu *menu, BOOL confirm)
{
    void *container = func_ov039_020bc1dc();
    u16 *tileMap = UpdateScreenWidgetLayer(10);
    void *widget;

    SetEntrySlotsVisible(container, FindWidgetById(container, 2), !confirm);
    SetEntrySlotsVisible(container, FindWidgetById(container, 7), confirm);
    SetEntrySlotsVisible(container, FindWidgetById(container, 8), confirm);
    CallStateWidget(10, 3, 0x12, 0x1a, 3);
    if (confirm) {
        FillBackgroundLayerRect(menu->yesLayer, tileMap, 3, 0x13, 0xf);
        FillBackgroundLayerRect(menu->noLayer, tileMap, 0x11, 0x13, 0xf);
        widget = FindWidgetById(container, 8);
    } else {
        FillBackgroundLayerRect(menu->promptLayer, tileMap, 8, 0x12, 0xf);
        widget = FindWidgetById(container, 2);
    }
    SetFocusedWidget(container, widget);
    menu->confirmMode = confirm;
    MoveCursorToElement(func_ov039_020bc638(), widget, FALSE);
}
