#include "nitro/types.h"

extern u32 data_02056014;

extern void func_0202d328(void *archive, int extra);
extern void func_0202d0ac(void *archive, int extra);
extern void BindModelAnimations(void *param1, void *param2, void *archive, void *param4);

/* Guarded resource dispatch that clears one slot field. */
int DispatchResourceLoad(void *param1, void *param2, int *archive, void *param4)
{
    u32 savedGuard = data_02056014;
    data_02056014 = 1;
    if (*archive == 0x4850414b) {
        func_0202d328(archive, 1);
    } else {
        func_0202d0ac(archive, 0);
    }
    data_02056014 = savedGuard;
    BindModelAnimations(param1, param2, archive, param4);
    *(u32 *)((u8 *)param1 + 0xc) = 0;
    return 1;
}
