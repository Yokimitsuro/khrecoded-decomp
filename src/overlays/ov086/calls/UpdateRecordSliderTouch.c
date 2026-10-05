#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x134];
    int pageIndex;
    u8 pad_138[0x4];
    int cursorIndex;
    u8 pad_140[0x154 - 0x140];
    BOOL sliderHeld;
    u8 pad_158[0x1e0 - 0x158];
    u16 touchX;
    u16 touchY;
    u16 touching;
    u16 touchInvalid;
} Ov086Menu;

extern void func_ov086_020c14e0(Ov086Menu *menu, int position);

void UpdateRecordSliderTouch(Ov086Menu *menu)
{
    if ((menu->pageIndex == 6 && menu->cursorIndex == 1) || (menu->pageIndex != 6 && menu->cursorIndex != 0)) {
        if (menu->touching == 1) {
            int position;

            if (menu->touchInvalid != 0) {
                return;
            }
            position = menu->touchY - 0x30;
            if (position > 0x38) {
                position = 0x38;
            } else if (position < 0) {
                position = 0;
            }
            func_ov086_020c14e0(menu, position);
            return;
        }
    }
    menu->sliderHeld = FALSE;
}
