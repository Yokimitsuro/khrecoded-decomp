#include "nitro/types.h"

typedef struct TileScreen {
    u8 pad_00[8];
    u16 width;
    u16 height;
} TileScreen;

typedef struct TileWidget {
    u8 pad_00[2];
    s16 x;
    s16 y;
} TileWidget;

extern void GetWidgetTileDimensions(TileWidget *widget, int *widthOut, int *heightOut);

int ClipWidgetToScreen(TileScreen *screen, TileWidget *widget, int *xOut, int *yOut, int *widthOut,
                                int *heightOut)
{
    int screenWidth = screen->width;
    int screenHeight = screen->height;
    int width;
    int height;
    int x;
    int y;

    GetWidgetTileDimensions(widget, &width, &height);
    x = widget->x;
    if (x < 0) {
        width += x;
        x = 0;
    }
    if (x + width > screenWidth) {
        width -= (x + width) - screenWidth;
    }
    y = widget->y;
    if (y < 0) {
        height += y;
        y = 0;
    }
    if (y + height > screenHeight) {
        height -= (y + height) - screenHeight;
    }
    *xOut = x;
    *yOut = y;
    *widthOut = width;
    *heightOut = height;
    return screenWidth;
}


