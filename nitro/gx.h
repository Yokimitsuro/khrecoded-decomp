#ifndef NITRO_GX_H
#define NITRO_GX_H

#include "nitro/types.h"
#include "nitro/fx.h"
#include "nitro/hw.h"

#define GX_LCD_SIZE_X 256
#define GX_LCD_SIZE_Y 192

typedef enum GXTexFmt {
    GX_TEXFMT_NONE = 0,
    GX_TEXFMT_A3I5 = 1,
    GX_TEXFMT_PLTT4 = 2,
    GX_TEXFMT_PLTT16 = 3,
    GX_TEXFMT_PLTT256 = 4,
    GX_TEXFMT_COMP4x4 = 5,
    GX_TEXFMT_A5I3 = 6,
    GX_TEXFMT_DIRECT = 7
} GXTexFmt;

typedef enum GXOBJVRamModeChar {
    GX_OBJVRAMMODE_CHAR_2D = 0,
    GX_OBJVRAMMODE_CHAR_1D_32K = 1 << 4,
    GX_OBJVRAMMODE_CHAR_1D_64K = (1 << 4) | (1 << 20),
    GX_OBJVRAMMODE_CHAR_1D_128K = (1 << 4) | (2 << 20),
    GX_OBJVRAMMODE_CHAR_1D_256K = (1 << 4) | (3 << 20)
} GXOBJVRamModeChar;

#endif
