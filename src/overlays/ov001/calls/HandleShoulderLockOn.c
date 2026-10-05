#include "nitro/types.h"

typedef struct LockOnState {
    u32 flags;
    u8 pad_04[0x30];
    s32 holdTimer;
} LockOnState;

extern LockOnState *data_ov001_020a04a4;
extern s16 data_020604fc;
extern s16 data_02060500;

extern void func_ov001_0206afec(void);
extern void func_ov001_0206bb74(int open, BOOL withSound);

void HandleShoulderLockOn(BOOL selectTarget)
{
    LockOnState *state;
    int trigger;
    int held;

    state = data_ov001_020a04a4;
    held = data_020604fc;
    trigger = data_02060500;

    if (((trigger & 0x100) && (held & 0x200)) || ((held & 0x100) && (trigger & 0x200))) {
        if (state->holdTimer > 0x9000) {
            if (selectTarget) {
                func_ov001_0206afec();
            } else {
                state->flags |= 0x20;
            }
            state->holdTimer = 0;
        }
    } else if (!(held & 0x100) && !(held & 0x200) && (state->flags & 0x20)) {
        if (state->flags & 2) {
            func_ov001_0206bb74(0, TRUE);
        }
        state->flags &= ~0x20;
    }
}
