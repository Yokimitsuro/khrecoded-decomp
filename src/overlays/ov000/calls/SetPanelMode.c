#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x30];
    u32 mode;
    BOOL paramIsNonPositive;
    u8 pad_38[4];
    u32 elapsed;
    s32 param1;
} Panel;

void SetPanelMode(Panel *panel, u32 mode)
{
    if (panel->param1 > 0) {
        panel->paramIsNonPositive = FALSE;
    } else {
        panel->paramIsNonPositive = TRUE;
    }
    panel->mode = mode;
    panel->elapsed = 0;
}
