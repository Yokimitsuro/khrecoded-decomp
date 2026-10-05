#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18de0];
    u32 value;
} OverlayState;

extern OverlayState *data_ov001_020a0528;

u32 GetGlobalScaleValue(void)
{
    if (data_ov001_020a0528 != 0) {
        return data_ov001_020a0528->value;
    }
    return 0;
}
