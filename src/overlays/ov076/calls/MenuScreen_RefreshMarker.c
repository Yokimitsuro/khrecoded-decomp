#include "nitro/types.h"

typedef struct MarkerInfo {
    u8 pad_00[3];
    u8 visible;
    u16 x;
    u16 y;
} MarkerInfo;

typedef struct Widget {
    u8 pad_00[0x14];
    int handle;
} Widget;

typedef struct MenuScreen {
    u8 pad_00000[0x18];
    void *container;
    u8 pad_0001C[0x11c04 - 0x1c];
    MarkerInfo *marker;
} MenuScreen;

extern void func_ov076_020cb9c0(MenuScreen *screen);
extern Widget *FindWidgetById(void *container, int elementId);
extern void func_ov027_020b91e8(void *container, Widget *element, const s32 *position, int mode);
extern void func_0204f218(void *scene, int handle, int paletteId);
extern void func_ov027_020b95a0(void *container, Widget *element, BOOL visible);

void MenuScreen_RefreshMarker(MenuScreen *screen)
{
    func_ov076_020cb9c0(screen);
    if (screen->marker->visible) {
        Widget *marker = FindWidgetById(screen->container, 0x2a);
        s32 position[2];

        position[0] = screen->marker->x << 12;
        position[1] = screen->marker->y << 12;
        func_ov027_020b91e8(screen->container, marker, position, 0);
        func_0204f218(screen->container, marker->handle, 0);
        func_ov027_020b95a0(screen->container, marker, TRUE);
    }
}
