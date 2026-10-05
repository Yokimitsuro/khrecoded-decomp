#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SlotMenu {
    s32 state;
    u8 pad_00004[0x8];
    void *selection;
    u8 pad_00010[0x7fb0];
    u8 messageWindow[0xa2a4];
    VecFx32 cameraPos;
    u8 pad_12270[0x375c4];
    s32 transitionTimer;
} SlotMenu;

extern BOOL MessageWindow_IsFinished(void *window);
extern void *func_ov076_020c853c(SlotMenu *menu);
extern void SlotMenu_RefreshView(SlotMenu *menu);

void SlotMenu_UpdateMessageWait(SlotMenu *menu)
{
    VecFx32 startPos;

    if (MessageWindow_IsFinished(menu->messageWindow)) {
        if ((menu->selection = func_ov076_020c853c(menu)) != NULL) {
            startPos.x = 0x80000;
            startPos.y = 0x60000;
            startPos.z = 0x300000;
            menu->cameraPos = startPos;
            menu->cameraPos.x += 0x12c000;
            menu->transitionTimer = 0;
            menu->state = 10;
        } else {
            menu->state = 5;
        }
    }
    SlotMenu_RefreshView(menu);
}
