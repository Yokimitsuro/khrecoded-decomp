#include "nitro/types.h"

extern u16 gRecordCounters[2];

u16 GetSecondaryRecordCount(void)
{
    return gRecordCounters[1];
}
