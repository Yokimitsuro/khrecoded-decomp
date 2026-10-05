#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[4];
    s16 width;
    s16 height;
} SpriteSize;

typedef struct {
    u8 pad_00[0x1c];
    SpriteSize *sprite;
    u8 pad_20[4];
    u16 angle;
} OrbitSprite;

extern s32 data_0205fde4;
extern const s16 data_02053580[];
extern void SetSpriteRectIfIdle(void *rect, fx32 x, fx32 y, fx32 width, fx32 height);

void PlaceOrbitSpriteCorners(OrbitSprite *self)
{
    fx32 halfWidth;
    int angle;
    fx32 halfHeight;
    fx32 centerX;
    fx32 centerY;
    fx32 left;
    fx32 top;

    if (data_0205fde4 == 0) {
        angle = self->angle >> 4;
        centerX = data_02053580[(0x400 - angle) & 0xfff] * 0x38 + 0x80000;
        centerY = data_02053580[angle] * 0x38 + 0x60000;
        halfWidth = (self->sprite->width / 2) * 0x1000;
        halfHeight = (self->sprite->height / 2) * 0x1000;
        left = centerX - halfWidth;
        SetSpriteRectIfIdle(self->sprite, left, centerY + halfHeight, 0x1000, 0x1000);
        top = centerY - halfHeight;
        SetSpriteRectIfIdle(self->sprite, left, top, 0x1000, -0x1000);
        SetSpriteRectIfIdle(self->sprite, centerX + halfWidth, top, -0x1000, -0x1000);
        SetSpriteRectIfIdle(self->sprite, centerX + halfWidth, centerY + halfHeight, -0x1000, 0x1000);
    }
}
