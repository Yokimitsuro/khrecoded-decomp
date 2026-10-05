#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0xc0];
    s32 state;
} PanelState;

extern PanelState *data_0205fe24;

void SetPanelReadyState(int readyA, int readyB) {
    if (readyA != 0 && readyB != 0) {
        data_0205fe24->state = 0;
        return;
    }
    if (readyA != 0) {
        data_0205fe24->state = 2;
        return;
    }
    if (readyB != 0) {
        data_0205fe24->state = 1;
        return;
    }
    data_0205fe24->state = 3;
}
