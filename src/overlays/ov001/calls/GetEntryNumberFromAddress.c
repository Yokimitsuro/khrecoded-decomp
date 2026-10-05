#include "nitro/types.h"

u16 GetEntryNumberFromAddress(u32 *base, u32 address)
{
    u16 index = (address - *base) / 12;

    return index + 1;
}
