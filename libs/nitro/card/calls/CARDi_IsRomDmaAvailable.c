#include "libs/nitro/card/card_rom_internal.h"

extern void *OS_GetDTCMAddress(void);

BOOL CARDi_IsRomDmaAvailable(u32 dmaChannel, void *destination, u32 source,
                             u32 length)
{
    return dmaChannel <= MI_DMA_MAX_NUM &&
           length > 0 &&
           ((u32)destination & 31) == 0 &&
           ((u32)destination + length <= (u32)OS_GetITCMAddress() ||
            (u32)destination >= (u32)OS_GetITCMAddress() + HW_ITCM_SIZE) &&
           ((u32)destination + length <= (u32)OS_GetDTCMAddress() ||
            (u32)destination >= (u32)OS_GetDTCMAddress() + HW_DTCM_SIZE) &&
           ((source | length) & (CARD_ROM_PAGE_SIZE - 1)) == 0;
}
