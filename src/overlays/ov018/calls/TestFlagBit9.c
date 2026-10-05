#include "nitro/types.h"

BOOL TestFlagBit9(int object)
{
    if ((*(u16 *)(object + 0x50) & 0x200) != 0) {
        return TRUE;
    }
    return FALSE;
}
