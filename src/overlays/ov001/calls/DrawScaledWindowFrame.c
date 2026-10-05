#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MessageWindow {
    int layer;
    u8 pad_04[0xc];
    u16 x;
    u16 y;
    u16 width;
    u16 height;
} MessageWindow;

extern int func_ov001_0207123c(void);
extern void RefreshWindowHighlight(MessageWindow *window, int layer, int plane);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void func_ov001_020795f0(int target, int x, int y, int width, int height, fx32 scale);

void DrawScaledWindowFrame(MessageWindow *window, int target, int percent)
{
    int width;
    int height;

    func_ov001_0207123c();
    RefreshWindowHighlight(window, window->layer, 9);
    RefreshWindowHighlight(window, window->layer, 11);
    width = (FX_Div(percent * window->width, 0x64000) >> 12) - 1;
    height = (FX_Div(percent * window->height, 0x64000) >> 12) - 1;
    func_ov001_020795f0(target, window->x + (window->width - (width + 1)) / 2,
        window->y + (window->height - (height + 1)) / 2, width, height, 0xe000);
}
