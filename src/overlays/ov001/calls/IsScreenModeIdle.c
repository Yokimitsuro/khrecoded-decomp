#include "nitro/types.h"

typedef struct ScreenState {
    u32 flags;
} ScreenState;

extern ScreenState *data_ov001_020a04a0;

BOOL IsScreenModeIdle(void)
{
    ScreenState *screen = data_ov001_020a04a0;

    if (screen == NULL) {
        return TRUE;
    }
    if (!(screen->flags & 0xf)) {
        return TRUE;
    }
    return FALSE;
}
