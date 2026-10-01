#include "libs/nitro/card/card_rom_internal.h"

u32 CARDi_ReadRomStatusCore(void)
{
    u32 cardId = CARD_BOOT_ID;

    if (!(cardId & 0x20000000UL)) {
        return 0x20;
    }

    CARDi_SetRomOp(0xd6, 0);
    REG_MCCNT1 = CARDi_GetRomFlag(CARD_COMMAND_ID) & ~CARD_LATENCY1_MASK;
    while ((REG_MCCNT1 & CARD_DATA_READY) == 0) {
    }
    return REG_MCD1;
}
