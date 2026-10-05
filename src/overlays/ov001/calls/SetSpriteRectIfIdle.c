#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 x;
    fx32 y;
} Point2Fx32;

typedef struct {
    u8 pad_00[0x10];
    Point2Fx32 position;
    Point2Fx32 size;
} SpriteRect;

extern s32 data_0205fde4;
extern void func_ov001_0206ad1c(void *arg);

void SetSpriteRectIfIdle(SpriteRect *rect, fx32 x, fx32 y, fx32 width, fx32 height)
{
    Point2Fx32 position;
    Point2Fx32 size;

    if (data_0205fde4 == 0) {
        position.x = x;
        position.y = y;
        size.x = width;
        size.y = height;
        rect->size = size;
        rect->position = position;
        func_ov001_0206ad1c(rect);
    }
}
