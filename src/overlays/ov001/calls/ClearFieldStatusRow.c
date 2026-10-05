#include "nitro/types.h"

extern void *func_ov001_0207123c(void);
extern void *GetPanelLayerScreen(s32 layer);
extern void ClearTilemapRegion(void *dest, int column, int row, int width, int height);
extern void func_ov027_020b9d74(void *widgets, int layer, int x, int y, int width, int height);

void ClearFieldStatusRow(void)
{
    void *widgets = func_ov001_0207123c();
    int layer = 0xb;
    void *screen = GetPanelLayerScreen(0xb);

    if (screen == NULL) {
        func_ov027_020b9d74(widgets, layer, 0x16, 0, 10, 1);
    } else {
        ClearTilemapRegion(screen, 0x16, 0, 10, 1);
    }
}
