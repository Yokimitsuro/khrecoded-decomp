#include "nitro/types.h"

typedef struct ScreenState {
    u32 flags;
    u8 pad_04[0x60];
    u8 brightnessRestored;
} ScreenState;

extern ScreenState *data_ov001_020a04a0;
extern void SetBrightnessAndSyncMain(int value);

void RestoreBrightnessOnce(void)
{
    ScreenState *screen = data_ov001_020a04a0;
    u32 flags = screen->flags;

    if (!(flags & 0x20) && !screen->brightnessRestored && (flags & 1) && (flags & 0x80)) {
        if (!(flags & 0x100)) {
            SetBrightnessAndSyncMain(0);
        }
        data_ov001_020a04a0->brightnessRestored = 1;
    }
}
