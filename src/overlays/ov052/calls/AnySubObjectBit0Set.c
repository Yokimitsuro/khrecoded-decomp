#include "nitro/types.h"

extern BOOL IsBit0Set(u32 *flags);

BOOL AnySubObjectBit0Set(int entity)
{
    BOOL found = FALSE;
    int i;
    for (i = 0; i < 2; i++) {
        if (IsBit0Set((u32 *)(entity + 0xb68 + i * 0x230))) {
            found = TRUE;
            break;
        }
    }
    return found;
}
