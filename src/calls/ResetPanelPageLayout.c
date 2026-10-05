#include "nitro/types.h"

typedef struct NNSG2dScreenData {
    u16 screenWidth;
    u16 screenHeight;
    u16 colorMode;
    u16 screenFormat;
    u32 szByte;
    u32 rawData[1];
} NNSG2dScreenData;

typedef struct PanelState {
    u8 pad_00[0xc];
    u8 pages[0x5c];
    NNSG2dScreenData *screenData;
    u8 pad_6c[0x50];
    s32 splitLayout;
} PanelState;

extern PanelState *data_0205fe24;
extern void MIi_CpuClearFast(u32 data, void *dst, u32 size);
extern void SetPanelPageParams(void *pages, s32 index, u32 valueA, s32 valueB, u32 valueC, u32 valueD, u32 valueE, u32 valueF);

void ResetPanelPageLayout(void)
{
    BOOL fullLayout = FALSE;
    PanelState *panel = data_0205fe24;
    NNSG2dScreenData *screen = panel->screenData;

    if (panel->splitLayout == 0) {
        fullLayout = TRUE;
    }
    MIi_CpuClearFast(0, screen->rawData, screen->szByte);
    SetPanelPageParams(panel->pages, 2, 0, 0, 9, fullLayout ? 0xb : 8, 0xc, 2);
    if (!fullLayout) {
        SetPanelPageParams(panel->pages, 0, 0, 0, 10, 0xb, 0xb, 2);
        SetPanelPageParams(panel->pages, 1, 0xb, 0, 10, 0xd, 0xb, 2);
    }
}
