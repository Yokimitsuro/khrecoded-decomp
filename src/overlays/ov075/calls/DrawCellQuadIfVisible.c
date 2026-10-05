#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 width;
    s16 height;
    u32 texParams[2];
} MenuImage;

typedef struct {
    u16 width;
    u16 height;
} CellSize;

typedef struct {
    const MenuImage *image;
    s16 x;
    s16 y;
    fx32 depth;
    u16 texOffsetS;
    u16 texOffsetT;
    u16 width;
    u16 height;
    u16 color;
} ImageQuad;

extern void InitCellImageQuad(ImageQuad *quad, const MenuImage *image, s16 x, s16 y, fx32 depth, u16 color,
                                CellSize cell);
extern void func_ov075_020cd874(ImageQuad *quad, BOOL highlighted);

void DrawCellQuadIfVisible(const MenuImage *image, int x, int y, int depth, u16 color, CellSize cell,
                                    BOOL highlighted)
{
    ImageQuad quad;

    if (x + image->width > 0 && x < 256 && y + image->height > 0 && y < 192) {
        InitCellImageQuad(&quad, image, x, y, depth << 12, color, cell);
        func_ov075_020cd874(&quad, highlighted);
    }
}