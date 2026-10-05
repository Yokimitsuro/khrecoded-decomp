#include "nitro/types.h"

typedef struct InputRecord {
    u16 x;
    u16 y;
    u16 touching;
    u16 invalid;
} InputRecord;

extern InputRecord *data_ov027_020ba3e0;

void ClearCapturedTouchState(void)
{
    data_ov027_020ba3e0->touching = 0;
}
