#include "nitro/types.h"

extern int IsDeviceReady(void);

u16 GetTransitionFrame(void)
{
    if (IsDeviceReady() != 0) {
        return 0x8000;
    }
    return *(u16 *)0x2fffcfa;
}
