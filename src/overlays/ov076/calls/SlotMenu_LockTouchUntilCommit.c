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

extern void *func_ov039_020bc1dc(void);
extern void SetWidgetRootTouchEnabled(void *root, BOOL enabled);
extern void SlotMenu_CommitSlotEdit(SlotMenu *menu);

void SlotMenu_LockTouchUntilCommit(SlotMenu *menu, BOOL unused)
{
    MenuCallback callback;

    SetWidgetRootTouchEnabled(func_ov039_020bc1dc(), FALSE);
    callback.handler = SlotMenu_CommitSlotEdit;
    callback.context = menu;
    menu->onReturn = callback;
}
