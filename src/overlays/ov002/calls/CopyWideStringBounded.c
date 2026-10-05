#include "nitro/types.h"

extern int GetWideStringLength(const u16 *text);
extern void func_01ff8ad8(const void *src, void *dst, u32 size);

u16 *CopyWideStringBounded(u16 *dst, const u16 *src, int maxLength)
{
    int length = GetWideStringLength(src);
    if (length <= maxLength) {
        func_01ff8ad8(src, dst, length * 2);
        dst[length] = 0;
    } else {
        func_01ff8ad8(src, dst, maxLength * 2);
    }
    dst[maxLength] = 0;
    return dst;
}
