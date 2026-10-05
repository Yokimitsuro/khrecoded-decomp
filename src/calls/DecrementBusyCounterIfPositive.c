#include "nitro/types.h"

typedef struct {
    u8 flag;
    u8 pad_01;
    s16 count;
} BusyCounterState;

extern BusyCounterState gBusyCounterState;

void DecrementBusyCounterIfPositive(void)
{
    if (gBusyCounterState.count > 0) {
        gBusyCounterState.count--;
    }
}
