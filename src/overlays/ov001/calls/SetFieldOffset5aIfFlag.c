#include "nitro/types.h"

void
SetFieldOffset5aIfFlag(int self, u8 value, int flag)
{
    if (flag != 0) {
        *(u8 *)(self + 0x5a) = value;
    }
}
