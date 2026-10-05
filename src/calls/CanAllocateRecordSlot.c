#include "nitro/types.h"

extern u8 *data_0205fe0c;
extern u16 data_0205fec4[];

BOOL CanAllocateRecordSlot(int index)
{
    u8 *counters = data_0205fe0c + 0x28d8;

    if (index >= 0 && index <= 0x7f)
    {
        u8 counter = counters[index];
        u16 *table = data_0205fec4;

        if (counter == 0 || table[0x80] < table[0x81])
        {
            return TRUE;
        }
        return FALSE;
    }
    return counters[index] < 0x63;
}
