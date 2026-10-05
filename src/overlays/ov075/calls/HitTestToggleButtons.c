#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_00[0x34];
    fx32 x;
    fx32 y;
} ButtonNode;

typedef struct {
    s16 x;
    s16 y;
} TouchPoint;

typedef struct {
    u8 pad_00[4];
    TouchPoint point;
    u16 flags;
} TouchState;

typedef struct {
    u8 pad_00000[0x7f90];
    TouchState *touch;
    u8 pad_7f94[0x11e4c - 0x7f94];
    ButtonNode *leftButton;
    u8 pad_11e50[4];
    ButtonNode *rightButton;
} MatrixMenu;

static inline u16 AbsS16(s16 value)
{
    s16 sign = value >> 15;
    return (value ^ sign) - sign;
}

int HitTestToggleButtons(MatrixMenu *menu)
{
    if ((menu->touch->flags & 3) == 1) {
        TouchPoint point;
        *(u32 *)&point = *(u32 *)&menu->touch->point;
        if (AbsS16(point.y - (menu->leftButton->y >> FX32_SHIFT)) <= 8) {
            if (AbsS16(point.x - (menu->leftButton->x >> FX32_SHIFT)) <= 0x2c) {
                return 0;
            }
            if (AbsS16(point.x - (menu->rightButton->x >> FX32_SHIFT)) <= 0x2c) {
                return 1;
            }
        }
    }
    return -1;
}
