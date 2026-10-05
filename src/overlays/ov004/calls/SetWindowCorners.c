#include "nitro/types.h"

typedef struct {
    u16 rows;
    u16 cols;
} WindowSize;

typedef struct {
    s16 x;
    s16 y;
} WindowPoint;

typedef struct {
    u8 pad_00[0x10];
    const WindowSize *size;
    u8 pad_14[0x10918 - 0x14];
    WindowPoint corners[2];
    WindowPoint extra;
} Window;

typedef struct {
    u8 pad_00[4];
    int anchor;
    u8 nudgeX : 4;
    u8 nudgeY : 4;
} WindowPlacement;

void SetWindowCorners(Window *window, const WindowPlacement *placement)
{
    switch (placement->anchor) {
    case 0:
    case 3:
    case 5:
        window->corners[0].x = 0;
        window->corners[1].x = (s16)(window->size->cols * 8 - 0x46 - placement->nudgeX);
        break;
    case 2:
    case 4:
    case 7:
        window->corners[0].x = (s16)(window->size->cols * 8 - 0x46 - placement->nudgeX);
        window->corners[1].x = 0;
        break;
    default:
        window->corners[0].x = window->corners[1].x = 0;
        break;
    }
    switch (placement->anchor) {
    case 0:
    case 1:
    case 2:
        window->corners[0].y = 0;
        window->corners[1].y = (s16)(window->size->rows * 8 - 0xc0 - placement->nudgeY);
        break;
    case 5:
    case 6:
    case 7:
        window->corners[0].y = (s16)(window->size->rows * 8 - 0xc0 - placement->nudgeY);
        window->corners[1].y = 0;
        break;
    default:
        window->corners[0].y = window->corners[1].y = 0;
        break;
    }
    window->extra.x = 0;
    window->extra.y = 0;
}
