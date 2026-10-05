#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18f40];
    u32 value;
} OverlayState;

extern OverlayState *data_ov001_020a0528;

void SetGlobalStateValue(u32 value)
{
    if (data_ov001_020a0528 != 0) {
        data_ov001_020a0528->value = value;
    }
}
