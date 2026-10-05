#include "nitro/types.h"

void SetFlagBit10(int object)
{
    *(u16 *)(object + 0x50) |= 0x400;
}
