#include "nitro/types.h"

typedef struct BusyCounterState {
    u8 flag;
    u8 pad_01;
    s16 count;
} BusyCounterState;

extern BusyCounterState gBusyCounterState;

BOOL IsBusyFlagSet(void)
{
    return gBusyCounterState.flag;
}
