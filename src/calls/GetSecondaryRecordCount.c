#include "nitro/types.h"

extern u16 data_0205ffc4[2];

u16 GetSecondaryRecordCount(void)
{
    return data_0205ffc4[1];
}
