#include "nitro/types.h"

typedef struct FadePanel {
    int state;
    u8 unknown_04[0xc];
    int elapsed;
} FadePanel;

extern int FX_Div(int numer, int denom);
extern void func_ov036_020bee60(FadePanel *panel);
extern void func_ov036_020c1d9c(FadePanel *panel, int ratio);
extern void SetTimerDuration(FadePanel *panel, int duration);
extern void SetDisplayLayersVisible(FadePanel *panel, BOOL enable);

void StepPanelFadeOut(FadePanel *panel) {
    int elapsed = panel->elapsed;
    int ratio;

    if (elapsed == 0) {
        func_ov036_020bee60(panel);
    } else {
        switch (panel->state) {
        case 0:
            SetTimerDuration(panel, 10);
            break;
        case 1:
        case 2:
        case 3:
        case 4:
            ratio = 0x1000 - FX_Div(elapsed > 0 ? (int)(0.5f + (float)(elapsed << 12))
                                                         : (int)((float)(elapsed << 12) - 0.5f),
                                             0x2000);
            if (panel->state == 4) {
                ratio = 0;
                SetDisplayLayersVisible(panel, FALSE);
            }
            func_ov036_020c1d9c(panel, ratio);
            if (ratio == 0) {
                SetTimerDuration(panel, 10);
            }
            break;
        }
    }
    panel->elapsed++;
}
