#include "nitro/types.h"

extern int GetWideStringLength(const u16 *text);
extern void func_01ff8ad8(const void *src, void *dst, u32 len);

u16 *CopyWideString(u16 *dst, const u16 *src)
{
    int length = GetWideStringLength(src);
    func_01ff8ad8(src, dst, length * 2);
    dst[length] = 0;
    return dst;
}
