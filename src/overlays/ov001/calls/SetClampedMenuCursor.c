#include "nitro/types.h"

typedef struct MenuState {
    u8 pad_00[0x50];
    u32 isOpen : 1;
    u32 flags : 31;
    u8 pad_54[0x72];
    u16 maxCursor;
} MenuState;

extern MenuState *data_ov001_020a04cc;
extern void func_ov001_02074b7c(u32 cursor, int animate);

void SetClampedMenuCursor(u32 cursor, int animate)
{
    MenuState *menu = data_ov001_020a04cc;

    if (menu->isOpen) {
        if (cursor > menu->maxCursor) {
            cursor = menu->maxCursor;
        }
        func_ov001_02074b7c(cursor, animate);
    }
}
