#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x6678];
    u32 field;
} Panel;

extern void PXI_Init_0202a64c(u32 field);
extern void SetupDisplayBanksAndLayers(Panel *panel);

void ReleaseFieldAndReset(Panel *panel)
{
    PXI_Init_0202a64c(panel->field);
    panel->field = 0;
    SetupDisplayBanksAndLayers(panel);
}
