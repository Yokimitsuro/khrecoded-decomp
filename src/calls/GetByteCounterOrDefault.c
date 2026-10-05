#include "nitro/types.h"

extern u16 data_0205fec4[];
extern u8 *data_0205fe0c;

u16 GetByteCounterOrDefault(int index)
{
    int result;
    if (index >= 0 && index <= 0x7f)
    {
        result = data_0205fec4[index];
    }
    else
    {
        result = *(u8 *)(data_0205fe0c + 0x28d8 + index);
    }
    return result;
}
