#include "libs/nitro/card/card_event_internal.h"

extern int OS_TryLockCard(u16 lockID);

BOOL CARDi_LockBusCondition(void *userdata)
{
    u16 lockID = *(const u16 *)userdata;
    return OS_TryLockCard(lockID) == 0;
}
