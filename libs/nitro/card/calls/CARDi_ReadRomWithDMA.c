#include "libs/nitro/card/card_rom_internal.h"

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void OS_SetIrqFunction(u32 mask, void (*function)(void));
extern u32 OS_ResetRequestIrqMask(u32 mask);
extern u32 OS_EnableIrqMask(u32 mask);
extern void CARDi_DmaReadPageCallback(void);

void CARDi_ReadRomWithDMA(CARDTransferInfo *info)
{
    OSIntrMode state = OS_DisableInterrupts();

    sCardRomState.dmaReadRegisteredInfo = info;
    OS_SetIrqFunction(OS_IE_CARD_DATA, CARDi_DmaReadPageCallback);
    (void)OS_ResetRequestIrqMask(OS_IE_CARD_DATA);
    (void)OS_EnableIrqMask(OS_IE_CARD_DATA);
    (void)OS_RestoreInterrupts(state);

    cardi_common.dmaInterface->receive(cardi_common.dmaChannel,
                                       (void *)&REG_MCD1,
                                       (void *)info->dst,
                                       CARD_ROM_PAGE_SIZE);
    CARDi_StartRomPageTransfer(info->src);
}
