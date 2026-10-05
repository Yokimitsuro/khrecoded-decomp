#include "nitro/types.h"

/* Fills a rectangular region of a strided grid. */
void FillGridRegion(u32 *base, u32 value, int stride, int start, u32 width, u32 height)
{
    u32 col;
    u32 row;
    int rowBase;

    for (row = 0; row < height; row++) {
        rowBase = start + row * stride;
        for (col = 0; col < width; col++) {
            base[rowBase + col] = value;
        }
    }
}
