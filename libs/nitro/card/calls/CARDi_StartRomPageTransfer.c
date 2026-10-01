#include "libs/nitro/card/card_rom_internal.h"

void CARDi_StartRomPageTransfer(u32 offset)
{
    CARDi_SetRomOp(0xb7, offset);
    REG_MCCNT1 = CARDi_GetRomFlag(CARD_COMMAND_PAGE);
}
