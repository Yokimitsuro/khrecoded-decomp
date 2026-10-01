#include "libs/nitro/card/card_rom_internal.h"

void CARDi_SetRomOp(u32 command, u32 offset)
{
    u32 cmd1 = (offset >> 8) | (command << 24);
    u32 cmd2 = offset << 24;

    while ((REG_MCCNT1 & CARD_START) != 0) {
    }

    REG_MCCNT0 = (u16)(0xc000 | (REG_MCCNT0 & ~0x2000));
    REG_MCCMD0 = MI_HToBE32(cmd1);
    REG_MCCMD1 = MI_HToBE32(cmd2);
}
