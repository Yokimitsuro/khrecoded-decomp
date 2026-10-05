#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_00[0x4];
    s16 width;
    s16 height;
} FrameSprite;

typedef struct {
    u8 pad_00[0x4];
    void *corners[4];
    u8 pad_14[0x18 - 0x14];
    FrameSprite *frame;
} FrameLayout;

extern s32 data_0205fde4;
extern void func_ov001_0206ad1c(void *arg);
extern void SetSpriteRectIfIdle(FrameSprite *rect, fx32 x, fx32 y, fx32 width, fx32 height);

void LayoutFrameCornerSprites(FrameLayout *layout) {
    FrameSprite *frame = layout->frame;
    int i;
    int halfWidth;
    int halfHeight;
    fx32 left;
    fx32 right;
    fx32 top;
    fx32 bottom;

    if (data_0205fde4 != 0) {
        return;
    }
    i = 0;
    halfWidth = frame->width / 2;
    halfHeight = frame->height / 2;
    do {
        func_ov001_0206ad1c(layout->corners[i]);
        i++;
    } while (i < 4);
    bottom = (halfHeight + 0x60) * FX32_ONE;
    left = (0x80 - halfWidth) * FX32_ONE;
    SetSpriteRectIfIdle(frame, left, bottom, FX32_ONE, FX32_ONE);
    top = (0x60 - halfHeight) * FX32_ONE;
    SetSpriteRectIfIdle(frame, left, top, FX32_ONE, -FX32_ONE);
    right = (halfWidth + 0x80) * FX32_ONE;
    SetSpriteRectIfIdle(frame, right, top, -FX32_ONE, -FX32_ONE);
    SetSpriteRectIfIdle(frame, right, bottom, -FX32_ONE, FX32_ONE);
}
