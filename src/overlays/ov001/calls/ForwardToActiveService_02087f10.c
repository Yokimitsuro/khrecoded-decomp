#include "nitro/types.h"

extern s32 data_ov001_0209f2e8;
extern void func_ov001_0209c554(void);

void ForwardToActiveService_02087f10(void)
{
    if (data_ov001_0209f2e8 != -1) {
        func_ov001_0209c554();
    }
}
