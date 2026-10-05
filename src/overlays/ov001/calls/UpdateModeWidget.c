#include "nitro/types.h"

typedef struct ModeState {
    u8 pad0[8];
    int active;
    u8 padC[0x10];
    u8 tween[0x18];
    u32 flag0 : 2;
    u32 freePending : 1;
} ModeState;

extern int *data_ov001_020a04e4;
extern int func_ov001_0207123c(void);
extern int func_ov027_020b9e10(int layer, int index);
extern void func_ov027_020b9e20(int layer, int index);
extern void SampleTweenValue(void *tween, s32 *value);
extern void DrawScaledWindowFrame(ModeState *state, int widget, s32 value);
extern void FreeModeResources(ModeState *state);

void UpdateModeWidget(ModeState *state) {
    s32 value;
    int layer = func_ov001_0207123c();
    int widget = func_ov027_020b9e10(layer, 0xb);

    SampleTweenValue(state->tween, &value);
    DrawScaledWindowFrame(state, widget, value);
    if (state->freePending) {
        if (*data_ov001_020a04e4 == 0) {
            state->active = 0;
            return;
        }
        FreeModeResources(state);
        *data_ov001_020a04e4 = 0;
    }
    func_ov027_020b9e20(layer, 0xb);
}
