#include "nitro/types.h"

extern u8 *gContinueScreenContext;
extern void LoadDefaultProjectionValues(u32 *values);

void ResetCameraProjectionOverrides(void)
{
    LoadDefaultProjectionValues((u32 *)(gContinueScreenContext + 0x198));
    *(u32 *)(gContinueScreenContext + 0x1b0) = 0x4cd;
    *(u32 *)(gContinueScreenContext + 0x1bc) = 0x4cd;
    *(u32 *)(gContinueScreenContext + 0x1c0) = 0x3000;
}
