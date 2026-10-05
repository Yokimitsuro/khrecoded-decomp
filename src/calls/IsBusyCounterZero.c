#include "nitro/types.h"

typedef struct {
    u8 flag;
    u8 pad_01;
    s16 count;
} BusyCounterState;

extern BusyCounterState gBusyCounterState;

BOOL IsBusyCounterZero(void)
{
    if (gBusyCounterState.count == 0) {
        return TRUE;
    }
    return FALSE;
}
