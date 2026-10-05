#include "nitro/types.h"

extern u32 IsScreenModeIdle(void);
extern void func_ov001_02063130(int a, u32 b);
extern void MarkFieldValueNegative(void);

u32 TryReenterState7(void)
{
    u32 result;

    result = IsScreenModeIdle();
    if (result != 0) {
        func_ov001_02063130(-3, 3);
        MarkFieldValueNegative();
        return 7;
    }
    return 0xffffffff;
}
