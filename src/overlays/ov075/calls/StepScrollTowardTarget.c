#include "nitro/types.h"

typedef struct {
    s16 x;
    s16 y;
} Point16;

typedef struct {
    u8 pad_00000[0x13eb8];
    Point16 scroll;
    Point16 scrollTarget;
} MatrixMenu;

static inline u16 AbsS16(s16 value)
{
    s16 sign = value >> 15;
    return (value ^ sign) - sign;
}

void StepScrollTowardTarget(MatrixMenu *menu)
{
    s16 delta;
    if (menu->scrollTarget.x != menu->scroll.x) {
        delta = menu->scrollTarget.x - menu->scroll.x;
        if (AbsS16(delta) >= 8) {
            menu->scroll.x += (s16)(delta < 0 ? -8 : 8);
        } else {
            menu->scroll.x = menu->scrollTarget.x;
        }
    } else if (menu->scrollTarget.y != menu->scroll.y) {
        delta = menu->scrollTarget.y - menu->scroll.y;
        if (AbsS16(delta) >= 8) {
            menu->scroll.y += (s16)(delta < 0 ? -8 : 8);
        } else {
            menu->scroll.y = menu->scrollTarget.y;
        }
    }
}
