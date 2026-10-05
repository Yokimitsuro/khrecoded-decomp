#include "nitro/types.h"

typedef struct {
    u8 pad0[0x10];
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u8 pad18[0xc8 - 0x18];
    int visible;
} Window;

extern int func_ov001_0207123c(void);
extern void func_ov027_020b9d74(int widgets, int layer, int x, int y, int width, int height);
extern void func_ov027_020b9d38(int widgets, int layer);

void RefreshWindowHighlight(Window *window, int unused, int layer) {
    int widgets = func_ov001_0207123c();
    if (window->visible != 0) {
        func_ov027_020b9d74(widgets, layer, window->x, window->y, window->width, window->height);
        return;
    }
    func_ov027_020b9d38(widgets, layer);
}
