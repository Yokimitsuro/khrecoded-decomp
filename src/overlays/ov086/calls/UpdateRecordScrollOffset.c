#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x134];
    int pageIndex;
    u8 pad_138[0x4];
    int cursorIndex;
    int scrollPos;
} Ov086Menu;

extern Ov086Menu *data_ov086_020c3020;

BOOL UpdateRecordScrollOffset(void)
{
    Ov086Menu *menu = data_ov086_020c3020;
    int offset;
    u32 value;

    if (menu->pageIndex != 7 && ((menu->pageIndex == 6 && menu->cursorIndex == 1) || (menu->pageIndex != 6 && menu->cursorIndex != 0))) {
        offset = menu->scrollPos * 0xac / 0x38;
    } else {
        offset = 0;
    }
    value = (offset << 16) & 0x1ff0000;
    *(vu32 *)0x04001014 = value;
    *(vu32 *)0x04001018 = value;
    return TRUE;
}
