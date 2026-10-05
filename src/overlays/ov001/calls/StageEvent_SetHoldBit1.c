#include "nitro/types.h"

extern int data_ov001_0209f2e8;
extern void func_ov001_0209b660(int eventIndex);

void StageEvent_SetHoldBit1(int eventIndex)
{
    if (data_ov001_0209f2e8 != -1) {
        func_ov001_0209b660(eventIndex);
    }
}
