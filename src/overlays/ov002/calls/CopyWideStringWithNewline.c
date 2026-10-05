#include "nitro/types.h"

extern int GetWideStringLength(const u16 *text);
extern void func_01ff8ad8(const void *src, void *dst, u32 len);

u16 *CopyWideStringWithNewline(u16 *dst, int unused, const u16 *src, int breakIndex)
{
    int length = GetWideStringLength(src);
    int remaining;

    func_01ff8ad8(src, dst, breakIndex * 2);
    remaining = length - breakIndex;
    dst[breakIndex] = '\n';
    if (remaining > 0) {
        func_01ff8ad8(src + breakIndex, dst + (breakIndex + 1), remaining * 2);
    }
    return dst;
}
