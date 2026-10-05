#include "nitro/types.h"

typedef struct FadePanel {
    int state;
    u8 unknown_04[0xc];
    int elapsed;
} FadePanel;

extern int FX_Div(int numer, int denom);
extern void func_ov036_020c1d9c(FadePanel *panel, int ratio);
extern void SetTimerDuration(FadePanel *panel, int duration);
extern void SetDisplayLayersVisible(FadePanel *panel, BOOL enable);

void StepPanelFade(FadePanel *panel) {
    int ratio;
    switch (panel->state) {
    case 0:
        SetTimerDuration(panel, 5);
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        ratio = FX_Div(panel->elapsed > 0 ? (int)(0.5f + (float)(panel->elapsed << 12))
                                                   : (int)((float)(panel->elapsed << 12) - 0.5f),
                                0x2000);
        if (panel->state == 4) {
            ratio = 0x1000;
        }
        func_ov036_020c1d9c(panel, ratio);
        if (ratio == 0x1000) {
            SetTimerDuration(panel, 5);
        }
        break;
    }
    SetDisplayLayersVisible(panel, TRUE);
    panel->elapsed++;
}
