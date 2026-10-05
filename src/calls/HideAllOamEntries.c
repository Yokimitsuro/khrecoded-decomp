#include "nitro/types.h"

void HideAllOamEntries(BOOL isMain)
{
    u32 *attr;
    u32 size;
    u32 i;

    if (isMain) {
        attr = (u32 *)0x07000000;
        size = 0x400;
    } else {
        attr = (u32 *)0x07000400;
        size = 0x400;
    }
    for (i = 0; i < size / 8; i++) {
        *attr = (*attr & ~0x300) | 0x200;
        attr += 2;
    }
}
