#include "libs/nitro/card/card_rom_internal.h"

void CARDi_ReadRomSyncCore(CARDiCommon *common)
{
    (void)sCardRomState.readRom(0, (void *)common->destination,
                                common->source, common->length);

    CARDi_CheckPulledOutCore(CARDi_ReadRomIDCore());
    CARDi_RefreshRom(CARD_ROMST_RFS_WARN_L2_MASK);
    cardi_common.command->result = 0;
}
