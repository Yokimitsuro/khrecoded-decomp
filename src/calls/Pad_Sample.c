#include "nitro/types.h"

typedef struct PadState {
    u16 held;
    u16 previous;
    u16 pressed;
} PadState;

extern PadState data_020604fc;
extern u32 data_02060504[];
extern u32 func_01ff80d4(void);

int Pad_Sample(void)
{
    u16 bit = 1;
    u16 previous;
    u16 held;
    u32 now;
    int keyIndex;

    data_020604fc.previous = data_020604fc.held;
    if ((*(volatile u16 *)0x02ffffa8 & 0x8000) >> 15) {
        held = 0;
    } else {
        u16 buttons = ((*(volatile u16 *)0x04000130 | *(volatile u16 *)0x02ffffa8) ^ 0x2fff) & 0x2fff;
        held = buttons & ~((buttons & 0x40) << 1) & ~((buttons & 0x20) >> 1);
    }
    data_020604fc.held = held;
    previous = data_020604fc.previous;
    held = (u16)data_020604fc.held;
    data_020604fc.pressed = ~previous & held;
    now = func_01ff80d4();
    for (keyIndex = 0; keyIndex < 12; keyIndex++) {
        if ((u16)(previous ^ held) & bit) {
            data_02060504[keyIndex] = now;
        }
        bit = bit << 1;
    }
    return 1;
}
