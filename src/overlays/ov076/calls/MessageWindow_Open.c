#include "nitro/types.h"

typedef struct WindowCallback {
    void (*func)(void *context);
    void *context;
} WindowCallback;

typedef struct MessageWindow {
    s32 state;
    u8 pad_0004[0x9c08 - 4];
    void *message;
    u8 pad_9C0C[0x9c38 - 0x9c0c];
    u32 finished : 1;
    u32 unk_9C38_1 : 1;
    u32 animating : 1;
    u16 boxWidth;
    u8 pad_9C3E[2];
    u16 scrollLine;
    u16 textSpeed;
    WindowCallback onAdvance;
    WindowCallback onDraw;
    WindowCallback onClose;
} MessageWindow;

extern void func_ov076_020cb888(void *context);

static inline int GX_GetVisiblePlane(void)
{
    return (int)((*(vu32 *)0x04000000 & 0x1f00) >> 8);
}

static inline void GX_SetVisiblePlane(int plane)
{
    *(vu32 *)0x04000000 = (u32)((*(vu32 *)0x04000000 & ~0x1f00) | (plane << 8));
}

void MessageWindow_Open(MessageWindow *window, void *message)
{
    WindowCallback none;
    WindowCallback draw;
    WindowCallback close;

    window->state = 4;
    window->finished = 1;
    none.func = NULL;
    none.context = NULL;
    window->onAdvance = none;
    draw.func = func_ov076_020cb888;
    draw.context = NULL;
    window->onDraw = draw;
    close.func = NULL;
    close.context = NULL;
    window->onClose = close;
    window->message = message;
    window->boxWidth = 0xf6;
    window->scrollLine = 0;
    window->textSpeed = 1;
    GX_SetVisiblePlane(GX_GetVisiblePlane() & ~2);
}
