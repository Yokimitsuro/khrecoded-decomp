#include "nitro/types.h"

extern BOOL func_ov016_020a41d0(u32 arg0, u32 arg1, void *obj, u32 arg3, u32 arg4);

BOOL ForwardModeCheck(u32 arg0, u32 arg1, void *obj, u32 arg3, u32 arg4)
{
    return func_ov016_020a41d0(arg0, arg1, obj, arg3, arg4);
}
