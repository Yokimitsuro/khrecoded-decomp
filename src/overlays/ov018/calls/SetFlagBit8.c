#include "nitro/types.h"

void SetFlagBit8(int object)
{
    *(u16 *)(object + 0x50) |= 0x100;
}
