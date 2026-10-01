#include "libs/nitro/card/card_rom_internal.h"

extern BOOL CARDi_Request(CARDiCommon *common, int requestType, int retryCount);

#define CARD_REQ_IDENTIFY 2
#define CARD_REQ_READ_BACKUP 6

void CARDi_IdentifyBackupCore(CARDiCommon *common)
{
    (void)CARDi_Request(common, CARD_REQ_IDENTIFY, 1);

    common->command->source = 0;
    common->command->destination = (u32)sCardBackupCachePageBuffer;
    common->command->length = 1;
    (void)CARDi_Request(common, CARD_REQ_READ_BACKUP, 1);
}
