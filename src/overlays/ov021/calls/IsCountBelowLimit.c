#include "nitro/types.h"

typedef struct Counter {
    u8 pad_00[0x3e];
    s8 limit;
    s8 count;
} Counter;

BOOL IsCountBelowLimit(Counter *counter)
{
    BOOL result = TRUE;
    if (counter->count >= counter->limit) {
        result = FALSE;
    }
    return result;
}
