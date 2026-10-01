#include "libs/nitro/card/card_rom_internal.h"

u32 CARDi_ReadRomIDCore(void)
{
    CARDi_SetRomOp(0xb8, 0);
    REG_MCCNT1 = CARDi_GetRomFlag(CARD_COMMAND_ID) & ~CARD_LATENCY1_MASK;
    while ((REG_MCCNT1 & CARD_DATA_READY) == 0) {
    }
    return REG_MCD1;
}
