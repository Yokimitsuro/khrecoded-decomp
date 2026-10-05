#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    u16 tileX;
    u16 tileY;
    u16 tileWidth;
    u8 pad_16[0x32];
    s32 focusX;
} MessageWindow;

int GetTailOverhang(MessageWindow *window)
{
    int tailX = (window->focusX + 4) / 8;
    int direction;
    int maxX;
    int clamped;
    int limit;

    if (tailX < 16) {
        direction = -1;
    } else {
        direction = 1;
    }
    tailX -= direction * 3;
    maxX = window->tileX + window->tileWidth - 3;
    if (tailX > maxX) {
        clamped = maxX;
    } else if (tailX < window->tileX + 1) {
        clamped = window->tileX + 1;
    } else {
        clamped = tailX;
    }
    limit = maxX - 2;
    if (clamped < limit) {
        limit = clamped;
    }
    return clamped - limit;
}
