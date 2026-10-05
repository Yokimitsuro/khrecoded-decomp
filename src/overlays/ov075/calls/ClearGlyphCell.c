#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x98];
    u8 *columnCount;
} GlyphGrid;

extern u64 DivModU32_02023fc8(u32 dividend, u32 divisor);

static inline void ClearPixelPair(u8 *pixels, u16 x, u16 y)
{
    u8 *cell = pixels + ((y & 7) * 4 + (y >> 3) * 0x300 + (x >> 3) * 32 + ((x & 7) >> 1));
    cell[0] = cell[1] = 0;
}

void ClearGlyphCell(u8 *pixels, GlyphGrid *grid, u32 cellIndex)
{
    u8 columns = *grid->columnCount;
    u32 top = (cellIndex / columns) * 4;
    u16 left = (cellIndex % columns) * 4;

    ClearPixelPair(pixels, left, top);
    ClearPixelPair(pixels, left, top + 1);
    ClearPixelPair(pixels, left, top + 2);
    ClearPixelPair(pixels, left, top + 3);
}
