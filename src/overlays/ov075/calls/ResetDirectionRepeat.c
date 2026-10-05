#include "nitro/types.h"

typedef struct {
    u8 pad_00000[0x13e7e];
    s8 repeatStep;
    u8 pad_13e7f[0x13eb4 - 0x13e7f];
    s16 repeatTimer;
    u16 heldDirection;
} MatrixMenu;

void ResetDirectionRepeat(MatrixMenu *menu)
{
    menu->heldDirection = 0;
    menu->repeatStep = 0;
    menu->repeatTimer = 0;
}
