#include "nitro/types.h"

typedef struct TaskManager {
    u16 activeIds[8];
    u8 activeCount;
    u8 secondaryCount;
} TaskManager;

extern TaskManager *data_ov001_020a0498;

void ClearSecondaryTaskCount(void)
{
    data_ov001_020a0498->secondaryCount = 0;
}
