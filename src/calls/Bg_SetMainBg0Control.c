#include "nitro/types.h"

extern int GX_GetBankForBGExtPltt(void);
extern void GX_SetGraphicsMode(int dispMode, int bgMode, int bg0As3d);

void Bg_SetMainBg0Control(int screenSize, int colorMode, int screenBase, int charBase)
{
    int bank = GX_GetBankForBGExtPltt();
    int extPalette;
    int bgMode;

    if (bank == 0x20 || bank == 0x10 || bank == 0x60) {
        extPalette = 0;
    } else {
        extPalette = 1;
    }
    bgMode = *(volatile u32 *)0x04000000 & 7;
    GX_SetGraphicsMode(1, bgMode, 0);
    {
        volatile u16 *bg0Control = (volatile u16 *)0x04000008;
        *bg0Control = (*bg0Control & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) |
                      (charBase << 2) | (extPalette << 13);
    }
}
