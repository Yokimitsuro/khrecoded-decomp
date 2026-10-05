#include "nitro/types.h"

typedef struct CursorState {
    u8 pad_00[0x20];
    s16 x;
    s16 y;
} CursorState;

extern CursorState *data_ov015_020812e0;

BOOL IsCursorOffscreen(void)
{
    CursorState *cursor = data_ov015_020812e0;
    BOOL offscreen = TRUE;

    if (cursor->x >= 0 && cursor->y >= 0) {
        offscreen = FALSE;
    }
    return offscreen != FALSE;
}
