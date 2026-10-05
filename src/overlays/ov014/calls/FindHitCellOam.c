#include "nitro/types.h"

extern int func_ov014_0206f5cc(u16 *cell, u16 index, int arg2, int arg3, int arg4, int arg5);

int FindHitCellOam(u16 *list, int arg2, int arg3, int arg4, int arg5)
{
    int i;
    int result = 0;
    int count = *list;

    for (i = result; i < count; i++) {
        result = func_ov014_0206f5cc(list, i, arg2, arg3, arg4, arg5);
        if (result != 0) {
            return result;
        }
    }
    return result;
}
