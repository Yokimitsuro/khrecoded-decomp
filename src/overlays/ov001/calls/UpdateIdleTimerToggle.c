#include "nitro/types.h"

typedef struct {
    u8 pad00[0x3c];
    int active;
    u8 pad40[0x107 - 0x40];
    u8 timer;
} IdleToggleState;

extern BOOL IsFieldFlag13OrSessionFlagSet(void);
extern signed char func_ov001_02068084(void);
extern BOOL func_ov001_020645c8(u32 id);
extern BOOL IsHudFlag7Set(void);
extern BOOL IsFieldFlag10Set(void);
extern BOOL IsFieldFlag8Set(void);
extern BOOL func_ov001_020642a0(void);
extern u32 func_ov001_0207b3f4(void);
extern BOOL func_ov001_0207b360(u32 arg);
extern s32 func_ov001_02063a38(void);

void UpdateIdleTimerToggle(IdleToggleState *state) {
    if (IsFieldFlag13OrSessionFlagSet()) {
        return;
    }
    if (func_ov001_02068084() == 5 && func_ov001_020645c8(0x3520)) {
        return;
    }
    if (IsHudFlag7Set() || IsFieldFlag10Set() || IsFieldFlag8Set()) {
        return;
    }
    if (state->active == 0) {
        state->timer = 0;
    }
    if (state->active == 0 && func_ov001_020642a0()) {
        if (func_ov001_0207b3f4() != 2 && func_ov001_0207b360(2)) {
            state->active = 1;
        }
    } else if (state->active != 0 && !func_ov001_020642a0()) {
        if (state->timer >= 0x3c) {
            func_ov001_0207b360(func_ov001_02063a38() == 10);
            state->active = 0;
        } else {
            state->timer++;
        }
    }
}
