#include "libs/nitro/card/card_rom_internal.h"

extern u32 OS_DisableIrqMask(u32 mask);
extern u32 OS_ResetRequestIrqMask(u32 mask);

void CARDi_DmaReadPageCallback(void)
{
    CARDTransferInfo *info = sCardRomState.dmaReadRegisteredInfo;

    if (info != 0) {
        info->src += CARD_ROM_PAGE_SIZE;
        info->dst += CARD_ROM_PAGE_SIZE;
        info->len -= CARD_ROM_PAGE_SIZE;

        if (info->len > 0) {
            CARDi_StartRomPageTransfer(info->src);
        } else {
            cardi_common.dmaInterface->stop(cardi_common.dmaChannel);
            (void)OS_DisableIrqMask(OS_IE_CARD_DATA);
            (void)OS_ResetRequestIrqMask(OS_IE_CARD_DATA);
            sCardRomState.dmaReadRegisteredInfo = 0;

            CARDi_CheckPulledOutCore(CARDi_ReadRomIDCore());
            if (info->callback != 0) {
                info->callback(info->userdata);
            }
        }
    }
}
