#include "nitro/types.h"

extern void DrawCenteredLabel(void);
extern void DrawPanelInfoText(void);
extern u8 *data_ov015_0207e960;

void ResetPanelExitFlags(void) {
    DrawCenteredLabel();
    DrawPanelInfoText();
    *(u32 *)(data_ov015_0207e960 + 0xe4) = 0;
    data_ov015_0207e960[0xba] = 0;
}
