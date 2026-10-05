#include "nitro/types.h"

extern u32 func_ov001_0206a814(void);
extern void func_ov001_02063130(int a, u32 b);
extern void func_ov001_0206430c(void);

u32 TryReenterState7(void)
{
    u32 result;

    result = func_ov001_0206a814();
    if (result != 0) {
        func_ov001_02063130(-3, 3);
        func_ov001_0206430c();
        return 7;
    }
    return 0xffffffff;
}
