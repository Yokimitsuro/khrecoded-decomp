#include "nitro/types.h"

extern void *data_0205fe24;
extern void AdjustPanelSlotSrcYAndDraw(void *state, int page, int delta);

void UpdatePanelSlotBlink(int slot)
{
    u8 *base = (u8 *)data_0205fe24;
    int byteOffset = slot * 8;
    u8 *timerBase = base + 0x74;
    s32 timer = *(s32 *)(timerBase + byteOffset) + 1;
    *(s32 *)(timerBase + byteOffset) = timer;
    if (timer >= 0x10) {
        s32 mode = (*(s32 *)(base + byteOffset + 0x78) == 1) ? 2 : 1;
        *(s32 *)(base + 0x78 + byteOffset) = mode;
        *(s32 *)(timerBase + byteOffset) = 0;
        AdjustPanelSlotSrcYAndDraw(base + 0xc, slot, *(s32 *)(base + 0x78 + byteOffset));
    }
}
