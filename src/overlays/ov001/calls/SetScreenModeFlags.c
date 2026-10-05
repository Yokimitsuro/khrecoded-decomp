#include "nitro/types.h"

typedef struct ScreenState {
    u32 flags;
} ScreenState;

extern ScreenState *data_ov001_020a04a0;

void SetScreenModeFlags(BOOL primary, int mode)
{
    data_ov001_020a04a0->flags &= ~0x10140;
    switch (mode) {
    case 0:
        data_ov001_020a04a0->flags |= primary ? 1 : 2;
        break;
    case 1:
        data_ov001_020a04a0->flags |= 0x40;
        data_ov001_020a04a0->flags |= primary ? 4 : 8;
        break;
    case 2:
        data_ov001_020a04a0->flags |= 0x50;
        data_ov001_020a04a0->flags |= primary ? 4 : 8;
        break;
    case 3:
        break;
    }
}
