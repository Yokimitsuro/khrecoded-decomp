#include "libs/nitro/card/card_rom_internal.h"

void CARDi_RefreshRomCore(void)
{
    CARDi_SetRomOp(0xb5, 0);
    REG_MCCNT1 = CARDi_GetRomFlag(0) & ~CARD_LATENCY1_MASK;
    while (REG_MCCNT1 & CARD_START) {
    }
}
