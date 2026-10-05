#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SpritePoint {
    fx32 x;
    fx32 y;
} SpritePoint;

typedef struct PopupSprite {
    u8 pad_00[0x10];
    SpritePoint position;
    fx32 scaleX;
    fx32 scaleY;
    u8 pad_20[4];
    u8 priority;
    u8 frame;
    u8 pad_26[4];
    u8 alpha : 5;
    u8 pad_2a_hi : 3;
    u8 pad_2b[5];
} PopupSprite;

typedef struct PopupSprites {
    PopupSprite main;
    PopupSprite side;
    u8 pad_60[0xa0 - 0x60];
    SpritePoint points[8];
    fx32 timers[16];
    u8 count;
} PopupSprites;

extern void func_ov001_0206ad28(PopupSprite *sprite);
extern fx32 EaseProgress(fx32 value, fx32 range, int mode);
extern fx32 FX_Mul(fx32 a, fx32 b);

void PopupSprites_Draw(PopupSprites *popup)
{
    u8 i;
    u8 count = popup->count;

    for (i = 0; i < count; i++) {
        fx32 scale;
        fx32 t;
        fx32 offset;
        SpritePoint pos;
        u8 side;

        popup->main.position = popup->points[i];
        popup->main.priority = 30 - i;
        popup->side.priority = 30 - i;
        func_ov001_0206ad28(&popup->main);
        if (popup->timers[i] != 0xa000) {
            popup->timers[i] += 0x1000;
            if (popup->timers[i] > 0xa000) {
                popup->timers[i] = 0xa000;
                goto settled;
            }
            t = EaseProgress(popup->timers[i], 0xa000, 3);
            scale = (fx32)(((s64)(0x1000 - t) * 0x2b33 + 0x800) >> 12) + (fx32)(((s64)t * 0x1000 + 0x800) >> 12);
            popup->side.alpha = (u8)((fx32)(((s64)EaseProgress(popup->timers[i], 0x7000, 0) * 0x1f000 + 0x800) >> 12) >> 12);
        } else {
settled:
            scale = 0x1000;
            popup->side.alpha = 31;
        }
        offset = FX_Mul(0xa000, scale);
        popup->side.scaleX = scale;
        popup->side.scaleY = scale;
        pos = popup->points[i];
        pos.x -= offset;
        for (side = 0; side < 2; side++) {
            popup->side.frame = side;
            if (side == 1) {
                pos.x += offset * 2;
            }
            popup->side.position = pos;
            func_ov001_0206ad28(&popup->side);
        }
    }
}
