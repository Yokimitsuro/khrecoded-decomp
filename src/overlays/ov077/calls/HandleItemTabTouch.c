#include "nitro/types.h"

typedef struct TouchState {
    u8 pad_00[0x4];
    s16 x;
    s16 y;
    u16 flags;
} TouchState;

typedef struct ItemScreen {
    u8 pad_00000[0x10];
    s32 touchHeld;
    u8 pad_00014[0x11ff8 - 0x14];
    s32 tab;
} ItemScreen;

typedef struct SaveState {
    u8 pad_0000[0x2c6a];
    u8 extraSlotCount;
} SaveState;

extern SaveState *data_0205fe0c;
extern TouchState *func_ov039_020bca20(void);
extern void PlaySoundEffect(int id, int channel);
extern void ShowSlotHeaderMessage(ItemScreen *screen);
extern void *func_ov039_020bc1dc(void);
extern void RefreshElementCellAnimation(void *container, int elementId);

BOOL HandleItemTabTouch(ItemScreen *screen)
{
    TouchState *touch = func_ov039_020bca20();
    s16 x = touch->x;
    s16 y = touch->y;
    u16 flags = touch->flags;
    int prevTab = screen->tab;
    u32 tabCount = data_0205fe0c->extraSlotCount + 1;
    int mode = flags & 3;

    switch (mode) {
    case 2:
        if (screen->touchHeld == 0) {
            return FALSE;
        }
        break;
    case 1:
        screen->touchHeld = 1;
    default:
        return FALSE;
    }
    screen->touchHeld = 0;
    if (x < 0x58 || x > 0xe0) {
        return FALSE;
    }
    if (y < 0x28) {
        return FALSE;
    }
    if (y < 0x38) {
        screen->tab = 0;
    } else if (y < 0x48) {
        screen->tab = 1;
    } else if (y < 0x60) {
        return FALSE;
    } else if (tabCount != 0 && y < 0x70) {
        screen->tab = 2;
    } else if (tabCount > 1 && y < 0x80) {
        screen->tab = 3;
    } else if (tabCount > 2 && y < 0x90) {
        screen->tab = 4;
    } else if (tabCount > 3 && y < 0xa0) {
        screen->tab = 5;
    } else {
        return FALSE;
    }
    if (screen->tab >= 2) {
        if (screen->tab == 5 && tabCount < 4) {
            screen->tab = 4;
        }
        if (screen->tab == 4 && tabCount < 3) {
            screen->tab = 3;
        }
        if (screen->tab == 3 && tabCount < 2) {
            screen->tab = 2;
        }
        if (screen->tab == 2 && tabCount < 1) {
            screen->tab = prevTab;
            return FALSE;
        }
    }
    if (screen->tab != prevTab) {
        PlaySoundEffect(1, 0);
        ShowSlotHeaderMessage(screen);
        RefreshElementCellAnimation(func_ov039_020bc1dc(), 0x2a);
        return FALSE;
    }
    touch->flags = 0;
    return TRUE;
}
