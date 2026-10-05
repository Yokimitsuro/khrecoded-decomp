#include "nitro/types.h"

extern void *gPanelState;
extern void AdjustPanelSlotSrcYAndDraw(void *state, int page, int delta);

void UpdatePanelPromptBlink(void)
{
    u8 *base = (u8 *)gPanelState;
    s32 *statusPtr = (s32 *)(base + 0x84);
    *(s32 *)(base + 0x84) = *(s32 *)(base + 0x84) + 1;
    s32 mode = statusPtr[1];
    if ((mode == 0 && statusPtr[0] >= 0x18) || (mode == 1 && statusPtr[0] >= 8)) {
        s32 newMode = (mode == 0) ? 1 : 0;
        statusPtr[1] = newMode;
        statusPtr[0] = 0;
        AdjustPanelSlotSrcYAndDraw(base + 0xc, 2, newMode);
    }
}
