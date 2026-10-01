#include "libs/nitro/gx/gx_load_state_internal.h"

#define GX_VRAM_BGEXTPLTT_NONE    0x0000
#define GX_VRAM_BGEXTPLTT_01_F    0x0020
#define GX_VRAM_BGEXTPLTT_23_G    0x0040
#define GX_VRAM_BGEXTPLTT_0123_E  0x0010
#define GX_VRAM_BGEXTPLTT_0123_FG 0x0060

extern GXVRamBGExtPltt GX_ResetBankForBGExtPltt(void);

void GX_BeginLoadBGExtPltt(void)
{
    gGXExtPlttLoadState.bgExtPltt = GX_ResetBankForBGExtPltt();

    switch (gGXExtPlttLoadState.bgExtPltt) {
    case GX_VRAM_BGEXTPLTT_0123_E:
        gGXExtPlttLoadState.bgExtPlttLCDCBase = 0x06880000;
        gGXExtPlttLoadState.bgExtPlttLCDCOffset = 0;
        break;
    case GX_VRAM_BGEXTPLTT_23_G:
        gGXExtPlttLoadState.bgExtPlttLCDCBase = 0x06894000;
        gGXExtPlttLoadState.bgExtPlttLCDCOffset = 0x4000;
        break;
    case GX_VRAM_BGEXTPLTT_0123_FG:
    case GX_VRAM_BGEXTPLTT_01_F:
        gGXExtPlttLoadState.bgExtPlttLCDCBase = 0x06890000;
        gGXExtPlttLoadState.bgExtPlttLCDCOffset = 0;
        break;
    case GX_VRAM_BGEXTPLTT_NONE:
    default:
        break;
    }
}
