#include "nitro/types.h"

extern u8 data_ov035_020bc434[][5];
extern void SetTilePixel4bpp_020bb8a4(void *target, void *layout, u16 column, int glyph);

void DrawMovieDigitRow(void *target, void *layout, int row)
{
    int i;

    for (i = 0; i < 5; i++) {
        SetTilePixel4bpp_020bb8a4(target, layout, i + 2, data_ov035_020bc434[row][i]);
    }
}