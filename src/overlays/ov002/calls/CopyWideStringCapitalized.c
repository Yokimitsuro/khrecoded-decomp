#include "nitro/types.h"

extern int GetWideStringLength(const u16 *text);
extern void func_01ff8ad8(const void *src, void *dst, u32 len);

u16 *CopyWideStringCapitalized(u16 *dst, const u16 *src)
{
    int length = GetWideStringLength(src);
    u16 first;

    func_01ff8ad8(src, dst, length * 2);
    first = dst[0];
    if (first >= 'a' && first <= 'z') {
        dst[0] = first - 0x20;
    }
    dst[length] = 0;
    return dst;
}
