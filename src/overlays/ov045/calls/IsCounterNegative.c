#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    s16 counter;
} Ov045CounterState;

extern Ov045CounterState *data_ov045_020c08a0;

/* Checks whether a counter field has gone negative. */
BOOL IsCounterNegative(void)
{
    if (data_ov045_020c08a0->counter < 0) {
        return TRUE;
    }
    return FALSE;
}
