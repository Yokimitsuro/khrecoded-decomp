#include "libs/nitro/card/card_rom_internal.h"

typedef void (*MIDmaCallback)(void *argument);


extern void CARD_CheckEnabled(void);
extern u32 CARDi_GetAccessLevel(void);
extern void OS_Terminate(void);
extern BOOL CARDi_WaitForTask(CARDiCommon *common, BOOL restart,
                              MIDmaCallback callback, void *argument);
extern const CARDDmaInterface *CARDi_GetDmaInterface(u32 channel);
extern void CARDi_ICInvalidateSmart(void *destination, u32 length, u32 threshold);
extern void CARDi_DCInvalidateSmart(void *destination, u32 length, u32 threshold);
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void CARDi_ReadRomWithDMA(CARDTransferInfo *info);
extern void CARD_WaitRomAsync(void);
extern BOOL CARDi_ExecuteOldTypeTask(void (*task)(CARDiCommon *), BOOL asynchronous);
extern void CARDi_ReadRomSyncCore(CARDiCommon *common);
extern void CARDi_DmaReadDone(void *argument);
extern int CARDi_ReadRomWithCPU(void *argument, void *buffer, u32 offset, u32 length);
extern BOOL CARDi_IsRomDmaAvailable(u32 dmaChannel, void *destination, u32 source,
                                    u32 length);

#define CARD_ACCESS_LEVEL_ROM 4
#define MI_DMA_NOT_USE (-1)

void CARDi_ReadRom(u32 dmaChannel, const void *source, void *destination,
                   u32 length, MIDmaCallback callback, void *argument,
                   BOOL asynchronous)
{
    CARDiCommon *common = &cardi_common;
    CARDTransferInfo *info;

    CARD_CheckEnabled();
    if ((CARDi_GetAccessLevel() & CARD_ACCESS_LEVEL_ROM) == 0) {
        OS_Terminate();
    }

    (void)CARDi_WaitForTask(common, 1, callback, argument);

    common->dmaInterface = CARDi_GetDmaInterface(dmaChannel);
    common->dmaChannel = common->dmaInterface != 0
                             ? dmaChannel & MI_DMA_MAX_NUM
                             : MI_DMA_NOT_USE;
    if (common->dmaChannel <= MI_DMA_MAX_NUM) {
        common->dmaInterface->stop(common->dmaChannel);
    }

    common->source = (u32)source + sCardRomState.romBase;
    common->destination = (u32)destination;
    common->length = length;

    sCardRomState.dmaReadInfo.callback = CARDi_DmaReadDone;
    sCardRomState.dmaReadInfo.userdata = 0;
    sCardRomState.dmaReadInfo.src = common->source;
    sCardRomState.dmaReadInfo.dst = common->destination;
    sCardRomState.dmaReadInfo.len = common->length;
    sCardRomState.dmaReadInfo.work = 0;

    if (sCardRomState.readRom == CARDi_ReadRomWithCPU &&
        CARDi_IsRomDmaAvailable(common->dmaChannel,
                                (void *)common->destination,
                                common->source, common->length)) {
        OSIntrMode state = OS_DisableInterrupts();

        if (sCardRomState.enableCacheInvalidationIC) {
            CARDi_ICInvalidateSmart((void *)common->destination,
                                    common->length,
                                    common->instructionFlushThreshold);
        }
        if (sCardRomConfig.enableCacheInvalidationDC) {
            CARDi_DCInvalidateSmart((void *)common->destination,
                                    common->length,
                                    common->dataFlushThreshold);
        }
        (void)OS_RestoreInterrupts(state);

        CARDi_ReadRomWithDMA(&sCardDmaReadInfo);
        if (!asynchronous) {
            CARD_WaitRomAsync();
        }
    } else {
        if (sCardRomState.enableCacheInvalidationIC) {
            CARDi_ICInvalidateSmart((void *)common->destination,
                                    common->length,
                                    common->instructionFlushThreshold);
        }
        (void)CARDi_ExecuteOldTypeTask(CARDi_ReadRomSyncCore, asynchronous);
    }
}
