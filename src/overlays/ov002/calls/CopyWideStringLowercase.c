#include "nitro/types.h"

extern int GetWideStringLength(const u16 *text);

void CopyWideStringLowercase(u16 *dst, const u16 *src)
{
    int length = GetWideStringLength(src);
    int index;

    for (index = 0; index < length; index++) {
        u16 ch = src[index];
        dst[index] = ch;
        if (ch >= 'A' && ch <= 'Z') {
            dst[index] = ch + 0x20;
        }
    }
}
