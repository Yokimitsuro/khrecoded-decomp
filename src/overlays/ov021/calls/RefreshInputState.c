#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    u16 status;
    u8 pending;
    u8 pad_07;
    u32 flags;
    u16 pressed;
    u16 held;
    u16 repeat;
    u8 pad_12[5];
    u8 locked;
    u8 lockTimer;
} InputState;

extern u16 data_020604fc;
extern u16 data_02060500;
extern u32 func_ov021_020af408(void);
extern BOOL Camera_IsFlag3JustSet(void);
extern int QuerySubModeStatus(void);

void RefreshInputState(InputState *state)
{
    BOOL query = TRUE;

    state->held = data_020604fc;
    state->pressed = data_02060500;
    state->repeat = 0;
    state->flags &= ~1;
    state->pending = 0;
    if (func_ov021_020af408() == 0) {
        if (state->locked) {
            query = FALSE;
        } else if (Camera_IsFlag3JustSet()) {
            query = FALSE;
            state->locked = 1;
            state->lockTimer = 0;
        }
    }
    if (query) {
        state->status = QuerySubModeStatus();
    }
}
