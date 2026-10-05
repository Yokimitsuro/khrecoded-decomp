#include "nitro/types.h"

extern void WM_StartDataSharing(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5);

void func_02012284(u32 param1, u32 param2)
{
    WM_StartDataSharing(param1, param2, 0xffff, 2, 1);
}
