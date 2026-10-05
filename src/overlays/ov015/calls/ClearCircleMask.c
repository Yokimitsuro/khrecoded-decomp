#include "nitro/types.h"

typedef struct {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} MaskRect;

BOOL ClearCircleMask(MaskRect *rect, u8 *mask, int radius)
{
    BOOL covered;
    int centerY;
    int top;
    int row;
    int col;
    int radiusSq;
    int x;
    int width;
    int height;
    int y;
    int centerX;

    radiusSq = radius * radius;
    covered = FALSE;
    if (rect != NULL) {
        width = rect->width;
        y = rect->y;
        x = rect->x;
        height = rect->height;
    } else {
        width = 0x90;
        y = 0;
        x = y;
        height = width;
    }
    top = y - 0x30;
    centerX = x + width / 2;
    centerY = top + height / 2;
    for (row = 0; row < height; row++) {
        col = 0;
        if (col < width) {
            do {
                int dy = centerY - (top + row);
                int dx = centerX - (x + col);
                if (dx * dx + dy * dy <= radiusSq) {
                    mask[(top + row) * 0x90 + x + col] = 0;
                }
            } while (++col < width);
        }
    }
    if (width < height) {
        width = height;
    }
    if (radius >= (int)(1.5f * (float)(width >> 1))) {
        covered = TRUE;
    }
    return covered;
}
