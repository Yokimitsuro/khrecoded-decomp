#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 words[6];
} PanelTransition;

typedef struct {
    u8 pad00[0x40];
    int prevState;
    int state;
    int savedState;
    PanelTransition transition;
} Panel;

extern Panel *data_ov044_020d0ec0;

extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void StartPanelTransition(const PanelTransition *transition, const VecFx32 *target, u32 data);

void StartScaledPanelTransition(const VecFx32 *target, fx32 distance, u32 data)
{
    Panel *panel = data_ov044_020d0ec0;
    PanelTransition transition = panel->transition;
    fx32 scale = FX_Div(distance, 0x64000);
    fx32 scaled;

    scaled = (fx32)(((s64)transition.words[2] * scale + 0x800) >> 12);
    if (panel->prevState != 6) {
        panel->savedState = panel->prevState;
    }
    transition.words[2] = scaled;
    StartPanelTransition(&transition, target, data);
}


