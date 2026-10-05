#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[4];
    s16 x;
    s16 y;
    u16 flags;
} TouchState;

typedef struct {
    u8 pad_00000[0xc];
    BOOL dragging;
    u8 pad_00010[0x34 - 0x10];
    fx32 scrollX;
    fx32 scrollY;
    u8 pad_0003c[0x68 - 0x3c];
    BOOL touchLocked;
    u8 pad_0006c[0x12dc0 - 0x6c];
    TouchState *touch;
} MatrixMenu;

extern u16 data_020604fc;
extern BOOL func_ov039_020bc0f4(void);

static inline BOOL IsTouchInactive(void)
{
    return func_ov039_020bc0f4() == 0;
}

void ScrollMatrixView(MatrixMenu *menu)
{
    TouchState *touch;
    u16 pad;

    if (IsTouchInactive()) {
        return;
    }
    touch = menu->touch;
    if ((touch->flags & 1) && menu->touchLocked == 0) {
        switch (touch->flags & 3) {
        case 1:
            menu->dragging = TRUE;
            return;
        case 2:
            menu->dragging = FALSE;
            return;
        case 3:
            if (!menu->dragging) {
                return;
            }
            menu->scrollX = (touch->x - 0x20) << 14;
            menu->scrollY = (touch->y - 0x18) << 14;
            if (menu->scrollX < 0) {
                menu->scrollX = 0;
            } else if (menu->scrollX > 0x2f0000) {
                menu->scrollX = 0x2f0000;
            }
            if (menu->scrollY < 0) {
                menu->scrollY = 0;
            } else if (menu->scrollY > 0x230000) {
                menu->scrollY = 0x230000;
            }
            return;
        }
        return;
    }
    pad = data_020604fc;
    if (pad & 0x40) {
        menu->scrollY -= 0xc000;
        if (menu->scrollY < 0) {
            menu->scrollY = 0;
        }
    } else if (pad & 0x80) {
        menu->scrollY += 0xc000;
        if (menu->scrollY > 0x230000) {
            menu->scrollY = 0x230000;
        }
    }
    if (pad & 0x20) {
        menu->scrollX -= 0xc000;
        if (menu->scrollX < 0) {
            menu->scrollX = 0;
        }
    } else if (pad & 0x10) {
        menu->scrollX += 0xc000;
        if (menu->scrollX > 0x2f0000) {
            menu->scrollX = 0x2f0000;
        }
    }
}
