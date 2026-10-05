#include "nitro/types.h"

typedef struct {
    u8 _0[0x44];
    int state;
} PanelState;

extern PanelState *data_ov044_020d0ec0;
extern void EnterPanelState(int state);

void ReapplyPanelState(void) {
    EnterPanelState(data_ov044_020d0ec0->state);
}
