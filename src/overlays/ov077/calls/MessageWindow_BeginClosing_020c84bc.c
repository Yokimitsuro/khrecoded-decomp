#include "nitro/types.h"

typedef struct PanelTween {
    u8 data[0x24];
} PanelTween;

typedef struct MessageWindow {
    s32 state;
    u8 pad_0004[0x9c14 - 4];
    PanelTween tween;
    u32 finished : 1;
    u32 unk_9C38_1 : 1;
    u32 animating : 1;
} MessageWindow;

extern void func_02052528(PanelTween *tween, int start, int end, int delay, int duration);
extern void func_02052570(PanelTween *tween);

void MessageWindow_BeginClosing_020c84bc(MessageWindow *window)
{
    if (window->state != 3) {
        window->state = 3;
        window->finished = 0;
        window->animating = 0;
        func_02052528(&window->tween, 0, 0x1000, 0, 0x50);
        func_02052570(&window->tween);
    }
}

