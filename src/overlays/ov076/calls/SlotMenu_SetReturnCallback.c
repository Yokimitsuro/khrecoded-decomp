#include "nitro/types.h"

typedef struct SlotMenu SlotMenu;

typedef struct MenuCallback {
    void (*handler)(SlotMenu *menu);
    SlotMenu *context;
} MenuCallback;

struct SlotMenu {
    u8 pad_00000[0x11c04];
    MenuCallback onReturn;
};

extern void func_ov076_020c4ec8(SlotMenu *menu);

void SlotMenu_SetReturnCallback(SlotMenu *menu)
{
    MenuCallback callback;
    callback.handler = func_ov076_020c4ec8;
    callback.context = menu;
    menu->onReturn = callback;
}
