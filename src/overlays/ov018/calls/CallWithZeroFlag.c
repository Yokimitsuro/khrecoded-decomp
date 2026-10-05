#include "nitro/types.h"

extern void func_ov018_020a35d8(int arg0, int arg1, int arg2, int arg3, int arg4, s8 arg5, s8 arg6, int flag);

void CallWithZeroFlag(int arg0, int arg1, int arg2, int arg3, int arg4, s8 arg5, s8 arg6)
{
    func_ov018_020a35d8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, 0);
}
