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

ImageQuad *InitCellImageQuad(ImageQuad *quad, const MenuImage *image, s16 x, s16 y, fx32 depth, u16 color,
                                      CellSize cell)
{
    u16 columns = image->width / cell.width;

    quad->image = image;
    quad->x = x;
    quad->y = y;
    quad->depth = depth;
    quad->texOffsetS = columns * cell.height;
    quad->texOffsetT = 0;
    quad->width = columns;
    quad->height = image->height;
    quad->color = color;    return quad;
}