#include "nitro/types.h"

typedef struct MovieContext {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[0x1e];
    s16 pendingInput;
} MovieContext;

extern MovieContext *data_ov035_020bc500;

BOOL IsMovieWaitingForInput(void)
{
    BOOL waiting = TRUE;

    if (data_ov035_020bc500->flags & 0x10) {
        waiting = FALSE;
    }
    if (data_ov035_020bc500->pendingInput >= 0) {
        waiting = FALSE;
    }
    return waiting;
}