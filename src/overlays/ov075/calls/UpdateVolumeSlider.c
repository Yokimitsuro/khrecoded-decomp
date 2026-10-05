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

typedef struct SliderRect {
    u8 width;
    u8 height;
    s8 marginX;
    s8 marginY;
} SliderRect;

typedef struct OptionMenu {
    u8 pad_00000[0x12dc0];
    TouchState *touch;
    u8 pad_12dc4[0x13464 - 0x12dc4];
    u8 sliderAnim[0x13e7e - 0x13464];
    s8 step;
    u8 pad_13e7f[0x13e88 - 0x13e7f];
    BOOL dragging;
    u8 pad_13e8c[0x13eb6 - 0x13e8c];
    u16 heldKeys;
} OptionMenu;

extern SliderRect data_ov075_020d1494;

extern int *func_01ffb2f8(void *anim, int frame, int value);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

static inline u16 AbsS16(s16 value)
{
    s16 sign = value >> 15;

    return (value ^ sign) - sign;
}

BOOL UpdateVolumeSlider(OptionMenu *menu, u8 *value, BOOL changed)
{
    BOOL tappedOutside = FALSE;
    u8 previous = *value;

    if (!changed) {
        TouchState *touch = menu->touch;
        u8 state = touch->state & 3;

        if (state != 0) {
            TouchPos pos = touch->pos;
            BOOL outside = TRUE;
            int offset;

            if (AbsS16(pos.x - 0x80) < (data_ov075_020d1494.width >> 1) + data_ov075_020d1494.marginX
                && AbsS16(pos.y - 0x60) < (data_ov075_020d1494.height >> 1) + data_ov075_020d1494.marginY) {
                outside = FALSE;
            }
            if (state == 1) {
                if (outside) {
                    tappedOutside = TRUE;
                } else {
                    menu->dragging = TRUE;
                }
            }
            if (menu->dragging && state != 2 && !outside) {
                offset = menu->touch->pos.x - 0x32;
                if (offset < 0) {
                    *value = 0;
                } else if (offset >= 0xa0) {
                    *value = 100;
                } else {
                    *value = offset * 100 / 0xa0;
                }
                changed = TRUE;
                goto apply;
            }
            menu->dragging = FALSE;
        } else {
            if (menu->heldKeys & 0xa0) {
                if (previous != 0) {
                    if (previous <= menu->step) {
                        *value = 0;
                    } else {
                        *value = previous - (u8)menu->step;
                    }
                    changed = TRUE;
                }
            } else if ((menu->heldKeys & 0x50) && previous < 100) {
                if (previous >= 100 - menu->step) {
                    *value = 100;
                } else {
                    *value = previous + (u8)menu->step;
                }
                changed = TRUE;
            }
            menu->dragging = FALSE;
        }
    }
apply:
    if (changed) {
        func_01ffb2f8(menu->sliderAnim, 0, *value << 12);
        if (*value != previous) {
            PlaySoundEffect(1, 10);
        }
    }
    return tappedOutside;
}
