#include "libs/nitro/card/card_rom_internal.h"

typedef void (*MIDmaCallback)(void *argument);

extern void CARDi_BeginBackupCommand(u32 accessLevel,
                                      MIDmaCallback callback, void *argument);
extern BOOL CARDi_ExecuteOldTypeTask(void (*task)(CARDiCommon *common),
                                     BOOL asynchronous);
extern void CARDi_RequestStreamCommandCore(CARDiCommon *common);

#define CARD_REQUEST_MODE_RECV 0
#define CARD_ACCESS_LEVEL_BACKUP_R 1
#define CARD_ACCESS_LEVEL_BACKUP_W 2

BOOL CARDi_RequestStreamCommand(u32 source, u32 destination, u32 length,
                                MIDmaCallback callback, void *argument,
                                BOOL asynchronous, u32 requestType,
                                int retryCount, u32 requestMode)
{
    u32 accessLevel = requestMode == CARD_REQUEST_MODE_RECV
                          ? CARD_ACCESS_LEVEL_BACKUP_R
                          : CARD_ACCESS_LEVEL_BACKUP_W;
    CARDiCommon *common;

    CARDi_BeginBackupCommand(accessLevel, callback, argument);

    common = &cardi_common;
    common->source = source;
    common->destination = destination;
    common->length = length;
    common->requestType = requestType;
    common->requestRetryCount = retryCount;
    common->requestMode = requestMode;

    return CARDi_ExecuteOldTypeTask(CARDi_RequestStreamCommandCore,
                                    asynchronous);
}
