#include "nitro/types.h"

typedef struct {
    u16 screenWidth;
    u16 screenHeight;
    u16 colorMode;
    u16 screenFormat;
    u32 szByte;
    u16 rawData[1];
} ScreenData;

extern void func_ov095_020bf370(void *dest, ScreenData *screen, int srcX, int srcY, int dstX, int dstY, int dstW, int dstH, int width, int height);

void LoadScreenRegion(void *dest, ScreenData *screen, int srcX, int srcY, int dstX, int dstY, int dstW, int dstH, int width, int height) {
    if (dstX < 0) {
        const int adjust = -dstX;
        srcX += adjust;
        width -= adjust;
        dstX = 0;
    }
    if (dstY < 0) {
        const int adjust = -dstY;
        srcY += adjust;
        height -= adjust;
        dstY = 0;
    }
    if (dstX + width > dstW) {
        const int adjust = (dstX + width) - dstW;
        width -= adjust;
    }
    if (dstY + height > dstH) {
        const int adjust = (dstY + height) - dstH;
        height -= adjust;
    }
    if (srcX < 0) {
        const int adjust = -srcX;
        dstX += adjust;
        width -= adjust;
        srcX = 0;
    }
    if (srcY < 0) {
        const int adjust = -srcY;
        dstY += adjust;
        height -= adjust;
        srcY = 0;
    }
    if (srcX + width > screen->screenWidth / 8) {
        const int adjust = (srcX + width) - (screen->screenWidth / 8);
        width -= adjust;
    }
    if (srcY + height > screen->screenHeight / 8) {
        const int adjust = (srcY + height) - (screen->screenHeight / 8);
        height -= adjust;
    }
    if (width <= 0 || height <= 0) {
        return;
    }
    switch (screen->screenFormat) {
    case 0:
        func_ov095_020bf370(dest, screen, srcX, srcY, dstX, dstY, dstW, dstH, width, height);
        break;
    case 1:
        break;
    case 2:
        break;
    default:
        break;
    }
}