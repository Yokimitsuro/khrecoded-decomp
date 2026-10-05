#include "nitro/types.h"

typedef struct Rect16 {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} Rect16;

int ComputeEmptyPixelPercent(const Rect16 *rect, const u8 *sheet)
{
    int row;
    int col;
    int empty;
    int left;
    int top;
    int width;
    int height;

    if (rect != NULL) {
        left = rect->x;
        top = rect->y;
        width = rect->width;
        height = rect->height;
    } else {
        left = 0;
        top = 0;
        width = 0x90;
        height = 0x90;
    }
    empty = 0;
    for (row = 0; row < height; row++) {
        for (col = 0; col < width; col++) {
            if (sheet[(top - 0x30 + row) * 0x90 + left + col] == 0) {
                empty++;
            }
        }
    }
    return empty * 100 / (width * height);
}
