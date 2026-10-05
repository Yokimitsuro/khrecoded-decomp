#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x38];
    s32 state;
    u8 pad_3c[4];
    u32 param1;
    u32 param2;
} Panel;

void SetPanelState(Panel *panel, s32 state, u32 param1, u32 param2)
{
    if (state != -1) {
        panel->state = state;
    }
    panel->param1 = param1;
    panel->param2 = param2;
}
