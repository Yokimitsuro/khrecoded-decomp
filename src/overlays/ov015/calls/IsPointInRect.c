#include "nitro/types.h"

typedef struct Rect16 {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} Rect16;

BOOL IsPointInRect(const Rect16 *rect, int x, int y)
{
    BOOL hit = FALSE;
    int left;
    int top;
    int right;
    int bottom;

    if (rect == NULL) {
        left = 0;
        top = 0;
        right = 0x100;
        bottom = 0xc0;
    } else {
        left = rect->x;
        top = rect->y;
        right = left + rect->width;
        bottom = top + rect->height;
    }
    if (left <= x && x < right && top <= y && y < bottom) {
        hit = TRUE;
    }
    return hit;
}
