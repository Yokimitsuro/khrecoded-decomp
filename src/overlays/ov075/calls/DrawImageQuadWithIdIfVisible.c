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

extern void func_ov075_020cd548(ImageQuad *quad, const MenuImage *image, s16 x, s16 y, fx32 depth, u16 color);
extern void func_ov075_020cda30(ImageQuad *quad, u32 polygonId);

void DrawImageQuadWithIdIfVisible(const MenuImage *image, int x, int y, int depth, u16 color, u32 polygonId)
{
    ImageQuad quad;

    if (x + image->width > 0 && x < 256 && y + image->height > 0 && y < 192) {
        func_ov075_020cd548(&quad, image, x, y, depth << 12, color);
        func_ov075_020cda30(&quad, polygonId);
    }
}
