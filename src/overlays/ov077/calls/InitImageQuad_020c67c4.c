#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 width;
    s16 height;
    u32 texParams[2];
} MenuImage;

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

void InitImageQuad_020c67c4(ImageQuad *quad, const MenuImage *image, s16 x, s16 y, fx32 depth, u16 color)
{
    quad->image = image;
    quad->x = x;
    quad->y = y;
    quad->depth = depth;
    quad->texOffsetS = 0;
    quad->texOffsetT = 0;
    quad->width = image->width;
    quad->height = image->height;
    quad->color = color;
}
