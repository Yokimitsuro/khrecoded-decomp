#include "nitro/types.h"

void
SetFieldOffset4c(int self, u32 value)
{
    *(u32 *)(self + 0x4c) = value;
}
