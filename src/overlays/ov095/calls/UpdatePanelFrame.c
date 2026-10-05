#include "nitro/types.h"

typedef struct {
    u8 pad[0x11148];
    int frameCounter;
    int blinkPhase;
} PanelWork;

typedef void (*PanelModeHandler)(PanelWork *work);

extern const PanelModeHandler gItemReportStateHandlers[];
extern int func_ov095_020c1228(PanelWork *work);
extern void InitSlotPool(PanelWork *work);
extern void DrawGridSprites(PanelWork *work);

void UpdatePanelFrame(PanelWork *work) {
    int mode = func_ov095_020c1228(work);

    if (gItemReportStateHandlers[mode] != NULL) {
        gItemReportStateHandlers[mode](work);
    }
    if (++work->frameCounter >= 8) {
        work->frameCounter = 0;
        work->blinkPhase = (work->blinkPhase + 1) % 2;
    }
    InitSlotPool(work);
    DrawGridSprites(work);
}