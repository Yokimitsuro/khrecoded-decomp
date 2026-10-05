#include "nitro/types.h"

extern s32 data_ov001_0209f2e8;
extern void func_ov001_0209c8ac(void);

void ForwardToActiveService(void)
{
    if (data_ov001_0209f2e8 != -1) {
        func_ov001_0209c8ac();
    }
}
