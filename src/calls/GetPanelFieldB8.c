#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0xa0];
    u32 field_a0;
    u8 pad_a4[0x14];
    u32 field_b8;
} PanelState;

extern PanelState *gPanelState;

u32 GetPanelFieldB8(void)
{
    return gPanelState->field_b8;
}
