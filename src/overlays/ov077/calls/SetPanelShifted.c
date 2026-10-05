#include "nitro/types.h"

#define REG_BG2OFS (*(volatile u32 *)0x04000018)

extern void func_ov077_020c5814(void *work, BOOL shifted);
extern void SyncScreenSpriteSlots(void *work, BOOL shifted);

static inline void G2_SetBG2Offset(int hOffset, int vOffset)
{
    REG_BG2OFS = (u32)((hOffset & 0x1ff) | ((vOffset & 0x1ff) << 16));
}

void SetPanelShifted(void *work, BOOL shifted)
{
    int offset;

    if (shifted) {
        offset = 0x20;
    } else {
        offset = 0;
    }
    G2_SetBG2Offset(offset, 0);
    func_ov077_020c5814(work, shifted);
    SyncScreenSpriteSlots(work, shifted);
}
