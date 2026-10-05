#include "nitro/types.h"

typedef struct {
    u8 pad_00000[0x13e7e];
    s8 repeatStep;
    u8 pad_13e7f[0x13eb4 - 0x13e7f];
    u16 repeatTimer;
    u16 heldDirection;
} MatrixMenu;

extern u16 data_020604fc;
extern void ResetDirectionRepeat(MatrixMenu *menu);

void UpdateDirectionRepeat(MatrixMenu *menu)
{
    if (menu->heldDirection != 0) {
        if (data_020604fc & menu->heldDirection) {
            menu->repeatTimer++;
            if (menu->repeatTimer == 10) {
                menu->repeatTimer = 0;
                menu->repeatStep++;
            }
        } else {
            ResetDirectionRepeat(menu);
        }
    } else {
        u16 pad = data_020604fc;
        BOOL pressed = (pad & 0xf0) ? TRUE : FALSE;
        u16 direction;
        direction = 0x40;
        if (pad & direction) {
            menu->heldDirection = direction;
        } else {
            direction = 0x80;
            if (pad & direction) {
                menu->heldDirection = direction;
            } else {
                direction = 0x20;
                if (pad & direction) {
                    menu->heldDirection = direction;
                } else {
                    direction = 0x10;
                    if (pad & direction) {
                        menu->heldDirection = direction;
                    }
                }
            }
        }
        if (pressed) {
            menu->repeatStep = 1;
            menu->repeatTimer = 1;
        }
    }
}
