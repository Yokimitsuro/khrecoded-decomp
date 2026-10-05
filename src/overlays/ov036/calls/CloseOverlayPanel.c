#include "nitro/types.h"

#define REG_DISPCNT (*(vu32 *)0x04000000)

extern void UploadAndFreeBgGraphics(void);
extern void ClosePanelAndResume(int panel);
extern void SelectActiveEntry(int index);
extern void G2x_SetBlendAlpha_(unsigned int *reg, unsigned int plane1, unsigned int plane2, unsigned int ev1, unsigned int ev2);

BOOL CloseOverlayPanel(int panel)
{
    u32 planes;

    UploadAndFreeBgGraphics();
    ClosePanelAndResume(panel);
    SelectActiveEntry(0);
    planes = (REG_DISPCNT & 0x1f00) >> 8;
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | ((planes | 0x10) << 8);
    G2x_SetBlendAlpha_((unsigned int *)0x04000050, 1, 0x22, 0, 0x10);
    return TRUE;
}
