#include "nitro/types.h"

typedef struct {
    u8 flag;
    u8 pad_01;
    s16 count;
} BusyCounterState;

extern BusyCounterState data_0205fde8;

void DecrementBusyCounterIfPositive(void)
{
    if (data_0205fde8.count > 0) {
        data_0205fde8.count--;
    }
}
