#include "nitro/types.h"

typedef struct MessageWindow {
    u8 pad_0000[0x9c38];
    s32 finished : 1;
} MessageWindow;

BOOL MessageWindow_IsFinished(MessageWindow *window)
{
    return window->finished;
}
