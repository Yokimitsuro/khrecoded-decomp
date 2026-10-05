#include "nitro/types.h"

extern void NNS_G2dSetAnimCtrlCallBackFunctorAtAnimFrame(void *entry, int fourth, int third, u16 fifth);

void SetupSlotEntry(u8 *owner, int index, int third, int fourth, u16 fifth)
{
    NNS_G2dSetAnimCtrlCallBackFunctorAtAnimFrame(owner + 0x18 + index * 0x8c, fourth, third, fifth);
}
