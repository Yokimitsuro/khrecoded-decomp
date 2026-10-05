#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0xb0];
    s32 pendingSoundReset;
    u8 pad_b4[4];
    s32 active;
    u8 pad_bc[4];
    s32 state;
    s32 inputLocked;
} PanelState;

extern PanelState *data_0205fe24;
extern u8 data_0205fdc4;
extern u16 data_02060500;
extern void SNDi_BroadcastChannelOp(int arg0);
extern void PlaySoundEffect(u32 a, u32 b);
extern void func_020281b0(void);
extern BOOL func_0202858c(void);
extern int InvokeCallbackSlot(int index);

BOOL UpdatePanelActivation(void)
{
    PanelState *panel = data_0205fe24;

    if (panel == NULL) {
        return FALSE;
    }
    if (panel->pendingSoundReset != 0) {
        SNDi_BroadcastChannelOp(1);
        PlaySoundEffect(0, 2);
        panel->pendingSoundReset = 0;
    }
    if (data_0205fdc4 == 0) {
        if (panel->active != 0) {
            func_020281b0();
        }
        return FALSE;
    }
    if (panel->active != 0) {
        return TRUE;
    }
    if (panel->inputLocked != 0) {
        return panel->active;
    }
    if (data_02060500 & 8) {
        if (!func_0202858c()) {
            return FALSE;
        }
        panel->state = 3;
        panel->active = InvokeCallbackSlot(0);
        return panel->active;
    }
    return FALSE;
}
