#include "nitro/types.h"

extern int data_ov001_0209f2e8;
extern void func_ov001_0209a19c(u32 eventIndex, int param);

void StageEvents_Trigger(u32 eventIndex, int param)
{
    if (data_ov001_0209f2e8 != -1) {
        func_ov001_0209a19c(eventIndex, param);
    }
}
