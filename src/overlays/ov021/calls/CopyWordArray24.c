#include "nitro/types.h"

void CopyWordArray24(int self, int dest)
{
    u32 *src;
    s32 byteOffset;
    u32 value;
    s32 index;

    src = (u32 *)(self + 0x1c);
    index = 0;
    do {
        value = *src;
        byteOffset = index * 4;
        index = index + 1;
        src = src + 1;
        *(u32 *)(dest + byteOffset) = value;
    } while (index < 0x18);
}
