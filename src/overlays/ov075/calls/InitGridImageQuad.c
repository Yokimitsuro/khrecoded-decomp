#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 width;
    s16 height;
    u32 texParams[2];
} MenuImage;

typedef struct {
    u8 columns;
    u8 rows;
    u8 column;
    u8 row;
} CellGrid;

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

ImageQuad *InitGridImageQuad(ImageQuad *quad, const MenuImage *image, s16 x, s16 y, fx32 depth, u16 color,
                                      CellGrid grid)
{
    u16 cellWidth = image->width / grid.columns;
    u16 cellHeight = image->height / grid.rows;

    quad->image = image;
    quad->x = x;
    quad->y = y;
    quad->depth = depth;
    quad->texOffsetS = cellWidth * grid.column;
    quad->texOffsetT = cellHeight * grid.row;
    quad->width = cellWidth;
    quad->height = cellHeight;
    quad->color = color;
    return quad;
}