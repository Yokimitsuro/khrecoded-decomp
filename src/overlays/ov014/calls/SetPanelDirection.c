#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_0000[0xcf92];
    u8 mode;
    s8 direction;
} PanelState;

extern PanelState *data_ov014_0206f9a0;

void SetPanelDirection(BOOL forward)
{
    s8 direction = -1;
    if (forward) {
        direction = 1;
    }
    data_ov014_0206f9a0->direction = direction;
    data_ov014_0206f9a0->mode = 4;
}
