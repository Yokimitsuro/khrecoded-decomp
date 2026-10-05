#include "nitro/types.h"

typedef struct {
    u8 flag;
    u8 pad_01;
    s16 count;
} BusyCounterState;

extern BusyCounterState data_0205fde8;

void IncrementBusyCounter(void)
{
    data_0205fde8.count++;
}
