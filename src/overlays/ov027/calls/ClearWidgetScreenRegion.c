#include "nitro/types.h"

typedef struct TileScreen TileScreen;
typedef struct TileWidget TileWidget;

extern int ClipWidgetToScreen(TileScreen *screen, TileWidget *widget, int *xOut, int *yOut, int *widthOut,
                                       int *heightOut);
extern void MIi_CpuClear16(u32 value, void *dst, u32 size);

void ClearWidgetScreenRegion(TileScreen *screen, TileWidget *widget, u16 *buffer)
{
    int x;
    int y;
    int width;
    int height;
    int row;
    int stride;

    if (buffer == NULL) {
        return;
    }
    stride = ClipWidgetToScreen(screen, widget, &x, &y, &width, &height);
    for (row = 0; row < height; row++) {
        MIi_CpuClear16(0, &buffer[stride * (y + row) + x], width * 2);
    }
}

