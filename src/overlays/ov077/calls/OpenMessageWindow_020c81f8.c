#include "nitro/types.h"

#define REG_DISPCNT (*(volatile u32 *)0x04000000)

typedef struct {
    void *func;
    void *context;
} DialogCallback;

typedef struct {
    s32 state;
    u8 pad_0004[0x9c08 - 4];
    u32 messageId;
    u8 pad_9c0c[0x9c38 - 0x9c0c];
    u32 active : 1;
    u16 highlightColor;
    u16 pad_9c3e;
    u16 scroll;
    u16 visible;
    DialogCallback callbacks[3];
} MessageWindow;

extern void func_ov077_020c88bc(u16 tag, void *info);

void OpenMessageWindow_020c81f8(MessageWindow *window, u32 messageId)
{
    DialogCallback confirm;
    DialogCallback cancel;
    DialogCallback select;
    u32 planes;

    window->state = 4;
    window->active = TRUE;
    confirm.func = NULL;
    confirm.context = NULL;
    window->callbacks[0] = confirm;
    cancel.func = func_ov077_020c88bc;
    cancel.context = NULL;
    window->callbacks[1] = cancel;
    select.func = NULL;
    select.context = NULL;
    window->callbacks[2] = select;
    window->messageId = messageId;
    window->highlightColor = 0xf6;
    window->scroll = 0;
    window->visible = 1;
    planes = (REG_DISPCNT & 0x1f00) >> 8;
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | ((planes & ~2) << 8);
}

