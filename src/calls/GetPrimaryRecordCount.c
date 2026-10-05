#include "nitro/types.h"

extern u16 gRecordCounters[2];

u16 GetPrimaryRecordCount(void)
{
    return gRecordCounters[0];
}
