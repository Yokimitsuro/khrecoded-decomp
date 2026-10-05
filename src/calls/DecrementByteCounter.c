#include "nitro/types.h"

extern u8 *data_0205fe0c;

void DecrementByteCounter(int index)
{
    u8 *slot = data_0205fe0c + 0x28d8 + index;
    *slot = *slot - 1;
}
