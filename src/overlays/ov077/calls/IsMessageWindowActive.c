#include "nitro/types.h"

typedef struct MessageWindow {
    u8 pad_0000[0x9c38];
    s32 active : 1;
} MessageWindow;

int IsMessageWindowActive(MessageWindow *window)
{
    return window->active;
}
