#include "nitro/types.h"

extern void func_0202845c(void *state, int page);

void AdjustPanelSlotSrcYAndDraw(void *state, int page, int delta)
{
    *(s32 *)((u8 *)state + 0x14 + page * 0x18) += delta * 2;
    func_0202845c(state, page);
    *(s32 *)((u8 *)state + 0x14 + page * 0x18) -= delta * 2;
}
