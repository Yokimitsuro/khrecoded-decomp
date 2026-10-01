#include "libs/nitro/card/card_rom_internal.h"

void CARDi_DmaReadDone(void *argument)
{
    (void)argument;

    CARDi_CheckPulledOutCore(CARDi_ReadRomIDCore());
    CARDi_RefreshRom(CARD_ROMST_RFS_WARN_L2_MASK);
    cardi_common.command->result = 0;
    CARDi_EndTask(&cardi_common);
}
