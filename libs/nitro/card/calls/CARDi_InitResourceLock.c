#include "libs/nitro/card/card_rom_internal.h"

void CARDi_InitResourceLock(void)
{
    CARDiCommon *const common = &cardi_common;

    common->lockOwner = -3;
    common->lockCount = 0;
    common->lockTarget = 0;
    common->lockQueue.head = common->lockQueue.tail = 0;
}
