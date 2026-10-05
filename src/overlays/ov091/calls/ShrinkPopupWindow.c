#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef float f32;

#define INT_TO_FX32(n) ((fx32)(((f32)(n) > 0) ? (0.5f + 4096.0f * (f32)(n)) : (4096.0f * (f32)(n) - 0.5f)))

typedef struct {
    s32 state;
    u32 flags;
    s32 stateTimer;
} PopupWindow;

extern void ClosePopupText(PopupWindow *window);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern void func_ov091_020c227c(PopupWindow *window, fx32 scale);
extern void SetPopupState(PopupWindow *window, s32 state);

void ShrinkPopupWindow(PopupWindow *window)
{
    fx32 scale;

    if (window->stateTimer == 0) {
        ClosePopupText(window);
    }
    scale = 0x1000 - FX_Div(INT_TO_FX32(window->stateTimer), 0x2000);
    func_ov091_020c227c(window, scale);
    if (scale == 0) {
        SetPopupState(window, 7);
    }
    window->stateTimer++;
}
