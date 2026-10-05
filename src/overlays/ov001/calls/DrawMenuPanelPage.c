#include "nitro/types.h"

typedef struct MenuPanel MenuPanel;
typedef void (*MenuPanelHandler)(MenuPanel *panel, int arg);

typedef struct MenuPanelHandlers {
    MenuPanelHandler handlers[6];
} MenuPanelHandlers;

struct MenuPanel {
    u8 pad_000[0xfc];
    int page;
    u8 pad_100[8];
    int handlerArg;
    u8 pad_10c[0x14];
    int hidden;
};

extern const MenuPanelHandlers gFieldMenuDrawHandlers;
extern void *GetSceneTagTracker(void);
extern void *func_ov001_0207123c(void);
extern void func_ov027_020b9d74(void *widgets, int layer, int x, int y, int width, int height);

void DrawMenuPanelPage(MenuPanel *panel)
{
    void *widgets;
    MenuPanelHandlers table;

    GetSceneTagTracker();
    widgets = func_ov001_0207123c();
    table = gFieldMenuDrawHandlers;
    if (panel->hidden == 0) {
        func_ov027_020b9d74(widgets, 11, 0, 16, 11, 8);
        if (table.handlers[panel->page] != NULL) {
            table.handlers[panel->page](panel, panel->handlerArg);
        }
    }
}
