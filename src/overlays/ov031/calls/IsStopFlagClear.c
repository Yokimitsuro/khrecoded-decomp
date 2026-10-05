#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
} OverlayState;

extern OverlayState *data_ov031_020bc820;

BOOL IsStopFlagClear(void)
{
    BOOL result = TRUE;
    if (data_ov031_020bc820->flags & 0x10) {
        result = FALSE;
    }
    return result;
}
