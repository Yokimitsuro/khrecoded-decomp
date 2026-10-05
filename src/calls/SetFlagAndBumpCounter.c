#include "nitro/types.h"

typedef struct Counter {
    u8 pad_00[2];
    u16 value;
} Counter;

extern Counter gRecordCounters;

void SetFlagAndBumpCounter(u8 *flag)
{
    if (*flag == 0) {
        *flag = *flag + 1;
        gRecordCounters.value += 1;
    }
}
