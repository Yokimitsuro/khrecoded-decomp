#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 x;
    fx32 y;
} Point2Fx32;

typedef struct {
    u8 pad_00[0x10];
    Point2Fx32 position;
} SpriteRect;

typedef struct {
    s32 isVisible;
    s32 isMirrored;
    fx32 height;
    SpriteRect *sprite;
} FallingPiece;

extern fx32 FX_Mul(fx32 left, fx32 right);
extern fx32 FX_Div(fx32 numer, fx32 denom);

void UpdateFallingPiecePosition(FallingPiece *piece)
{
    Point2Fx32 position;
    fx32 height = piece->height;

    if (height < -0x10000) {
        piece->isVisible = 0;
        return;
    }
    position.y = height;
    if (piece->isMirrored != 0) {
        position.x = FX_Div(FX_Mul(-0x52000, height), 0xC0000) + 0x98000;
    } else {
        position.x = FX_Div(FX_Mul(0x52000, height), 0xC0000) + 0x69000;
    }
    piece->sprite->position = position;
}
