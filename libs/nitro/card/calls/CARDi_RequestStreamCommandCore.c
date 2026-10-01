#include "libs/nitro/card/card_rom_internal.h"

u8 sCardBackupCachePageBuffer[0x100] __attribute__((aligned(32)));

extern void func_02000b64(const void *descriptor);
extern u32 CARD_GetBackupSectorSize(void);
extern void DC_InvalidateRange(void *address, u32 length);
extern void MI_CpuCopy8(const void *source, void *destination, u32 length);
extern void DC_FlushRange(const void *address, u32 length);
extern void DC_WaitWriteBufferEmpty(void);
extern BOOL CARDi_Request(CARDiCommon *common, int requestType, int retryCount);

#define cardi_backup_assert ((const void *)0x02000bac)
#define CARD_STAT_CANCEL 0x40
#define CARD_RESULT_CANCELED 7
#define CARD_REQ_VERIFY_BACKUP 9
#define CARD_REQ_ERASE_SECTOR_BACKUP 11
#define CARD_REQ_ERASE_SUBSECTOR_BACKUP 15
#define CARD_REQUEST_MODE_RECV 0
#define CARD_REQUEST_MODE_SEND 1
#define CARD_REQUEST_MODE_SEND_VERIFY 2
#define CARD_REQUEST_MODE_SPECIAL 3

void CARDi_RequestStreamCommandCore(CARDiCommon *common)
{
    const int requestType = common->requestType;
    const int requestMode = common->requestMode;
    const int retryCount = common->requestRetryCount;
    u32 size = sizeof(sCardBackupCachePageBuffer);

    func_02000b64(cardi_backup_assert);

    if (requestType == CARD_REQ_ERASE_SECTOR_BACKUP) {
        size = CARD_GetBackupSectorSize();
    } else if (requestType == CARD_REQ_ERASE_SUBSECTOR_BACKUP) {
        size = cardi_common.command->backup.subSectorSize;
    }

    do {
        const u32 length = size < common->length ? size : common->length;
        common->command->length = length;

        if ((common->flags & CARD_STAT_CANCEL) != 0) {
            common->flags &= ~CARD_STAT_CANCEL;
            common->command->result = CARD_RESULT_CANCELED;
            break;
        }

        switch (requestMode) {
        case CARD_REQUEST_MODE_RECV:
            DC_InvalidateRange(sCardBackupCachePageBuffer, length);
            common->command->source = common->source;
            common->command->destination = (u32)sCardBackupCachePageBuffer;
            break;
        case CARD_REQUEST_MODE_SEND:
        case CARD_REQUEST_MODE_SEND_VERIFY:
            MI_CpuCopy8((const void *)common->source,
                        sCardBackupCachePageBuffer, length);
            DC_FlushRange(sCardBackupCachePageBuffer, length);
            DC_WaitWriteBufferEmpty();
            common->command->source = (u32)sCardBackupCachePageBuffer;
            common->command->destination = common->destination;
            break;
        case CARD_REQUEST_MODE_SPECIAL:
            common->command->source = common->source;
            common->command->destination = common->destination;
            break;
        }

        if (!CARDi_Request(common, requestType, retryCount)) {
            break;
        }

        if (requestMode == CARD_REQUEST_MODE_SEND_VERIFY) {
            if (!CARDi_Request(common, CARD_REQ_VERIFY_BACKUP, 1)) {
                break;
            }
        } else if (requestMode == CARD_REQUEST_MODE_RECV) {
            MI_CpuCopy8(sCardBackupCachePageBuffer,
                        (void *)common->destination, length);
        }

        common->source += length;
        common->destination += length;
        common->length -= length;
    } while (common->length > 0);
}
