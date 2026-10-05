#include "nitro/types.h"

typedef struct FieldState {
    u8 pad_000[0x214];
    u32 lowFlags : 18;
    u32 fadeLocked : 1;
    u32 highFlags : 13;
} FieldState;

typedef struct FadeWindow {
    u8 pad_00[0x30];
    int state;
    BOOL started;
    BOOL enabled;
    u8 pad_3C[8];
    BOOL pendingReset;
    u8 pad_48[0x90];
    int mode;
} FadeWindow;

extern FieldState *data_ov001_020a0480;
extern void SetDisplaySetting(int setting);
extern int func_02029f6c(void);

void UpdateDisplayFadeState(FadeWindow *window)
{
    if (window->enabled) {
        if (window->started) {
            if (window->mode == 4) {
                window->state = 6;
                window->started = TRUE;
            } else if (!data_ov001_020a0480->fadeLocked) {
                SetDisplaySetting(0);
                if (window->pendingReset) {
                    window->state = 6;
                    window->pendingReset = FALSE;
                } else if (func_02029f6c() < 0) {
                    window->state = 4;
                } else if (func_02029f6c() > 0) {
                    window->state = 5;
                }
            }
        } else {
            window->state = 6;
            window->started = TRUE;
        }
    }
}
