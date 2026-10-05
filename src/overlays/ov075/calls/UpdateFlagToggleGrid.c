#include "nitro/types.h"

typedef union TouchPos {
    u32 raw;
    struct {
        s16 x;
        s16 y;
    };
} TouchPos;

typedef struct TouchState {
    u8 pad_00[4];
    TouchPos pos;
    u16 state;
} TouchState;

typedef struct ToggleRect {
    u8 width;
    u8 height;
    s8 marginX;
    s8 marginY;
} ToggleRect;

typedef struct OptionMenu {
    u8 pad_00000[0x12dc0];
    TouchState *touch;
    u8 pad_12dc4[0x13568 - 0x12dc4];
    u8 toggleAnim[0x13ec4 - 0x13568];
    u8 toggleCursor;
} OptionMenu;

extern ToggleRect data_ov075_020d1498;
extern u16 data_02060500;

extern int *func_01ffb2f8(void *anim, int frame, int value);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

static inline u16 AbsS16(s16 value)
{
    s16 sign = value >> 15;

    return (value ^ sign) - sign;
}

static inline BOOL IsTouchOutsidePanel(TouchState *touch)
{
    TouchPos pos = touch->pos;
    BOOL outside = TRUE;

    if (AbsS16(pos.x - 0x80) < (data_ov075_020d1498.width >> 1) + data_ov075_020d1498.marginX
        && AbsS16(pos.y - 0x60) < (data_ov075_020d1498.height >> 1) + data_ov075_020d1498.marginY) {
        outside = FALSE;
    }
    return outside;
}

BOOL UpdateFlagToggleGrid(OptionMenu *menu, u8 *flags, BOOL changed)
{
    BOOL tappedOutside = FALSE;
    u8 previous = *flags;
    u8 state;
    TouchState *touch;

    if (!changed) {
        touch = menu->touch;
        state = touch->state & 3;

        if (state != 0) {
            BOOL outside = IsTouchOutsidePanel(touch);
            TouchPos local;

            if (state == 1) {
                if (outside) {
                    tappedOutside = TRUE;
                } else {
                    local.raw = touch->pos.raw;
                    local.x -= 0x60;
                    local.y -= 0x68;
                    if (local.y > 0 && local.y < 0x20 && local.x >= 0 && local.x < 0x48) {
                        menu->toggleCursor = local.x / 0x18;
                        *flags ^= (u8)(1 << menu->toggleCursor);
                        changed = TRUE;
                    }
                }
            }
        } else {
            switch (data_02060500) {
            case 0x20:
                if (menu->toggleCursor != 0) {
                    menu->toggleCursor--;
                    PlaySoundEffect(1, 10);
                }
                changed = TRUE;
                break;
            case 0x10:
                if (menu->toggleCursor < 2) {
                    menu->toggleCursor++;
                    PlaySoundEffect(1, 10);
                }
                changed = TRUE;
                break;
            case 0x40:
                *flags = (u8)(1 << menu->toggleCursor) | previous;
                changed = TRUE;
                break;
            case 0x80:
                *flags = (u8)~(1 << menu->toggleCursor) & previous;
                changed = TRUE;
                break;
            }
        }
    }
    if (changed) {
        func_01ffb2f8(menu->toggleAnim, 3, *flags << 12);
        if (*flags != previous) {
            PlaySoundEffect(1, 10);
        }
    }
    return tappedOutside;
}
