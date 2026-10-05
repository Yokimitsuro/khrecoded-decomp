#include "nitro/types.h"

typedef struct Panel {
    u8 pad_00[0x30];
    s32 state;
    u8 pad_34[0x24];
    s32 nextState;
    u8 pad_5C[0x84];
    s32 brightness;
} Panel;

extern Panel *data_ov001_020a04e8;
extern int func_02029f6c(void);

void Panel_CaptureBrightness(void)
{
    Panel *panel;
    int brightness;

    panel = data_ov001_020a04e8;
    brightness = func_02029f6c();
    if (panel != NULL) {
        if (panel->state == 3 || (panel->state == 6 && (brightness <= -16 || brightness >= 16))) {
            panel->state = 3;
            panel->brightness = brightness;
            panel->nextState = 1;
        }
    }
}
