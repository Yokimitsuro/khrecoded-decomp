#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0xc0];
    s32 state;
} PanelState;

extern PanelState *gPanelState;

void SetPanelReadyState(int readyA, int readyB) {
    if (readyA != 0 && readyB != 0) {
        gPanelState->state = 0;
        return;
    }
    if (readyA != 0) {
        gPanelState->state = 2;
        return;
    }
    if (readyB != 0) {
        gPanelState->state = 1;
        return;
    }
    gPanelState->state = 3;
}
