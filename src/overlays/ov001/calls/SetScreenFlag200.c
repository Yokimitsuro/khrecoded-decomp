#include "nitro/types.h"

typedef struct ScreenState {
    u32 flags;
} ScreenState;

extern ScreenState *data_ov001_020a04a0;

void SetScreenFlag200(BOOL enable)
{
    if (enable) {
        data_ov001_020a04a0->flags |= 0x200;
        return;
    }
    data_ov001_020a04a0->flags &= ~0x200;
}
