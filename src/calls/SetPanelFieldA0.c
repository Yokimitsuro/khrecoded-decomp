#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0xa0];
    u32 field_a0;
} PanelState;

extern PanelState *gPanelState;

u32 SetPanelFieldA0(u32 value)
{
    gPanelState->field_a0 = value;
    return value;
}
