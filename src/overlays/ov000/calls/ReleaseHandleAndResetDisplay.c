#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x6690];
    u32 pxiHandle;
} Panel;

extern u32 func_ov000_02063770(void);
extern void PXI_Init_0202a64c(u32 handle);
extern void SetupDisplayBanksAndLayers(Panel *panel);

void ReleaseHandleAndResetDisplay(Panel *panel)
{
    BOOL needsReset = FALSE;

    if (func_ov000_02063770() == 2) {
        needsReset = TRUE;
    }
    PXI_Init_0202a64c(panel->pxiHandle);
    panel->pxiHandle = 0;
    if (needsReset) {
        SetupDisplayBanksAndLayers(panel);
    }
}
