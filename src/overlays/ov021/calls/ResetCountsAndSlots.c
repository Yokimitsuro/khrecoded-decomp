#include "nitro/types.h"

typedef struct SlotCounter {
    u8 pad_00[0x3f];
    u8 count;
    u8 cursor;
} SlotCounter;

extern void ResetEntryStates(SlotCounter *counter);

void ResetCountsAndSlots(SlotCounter *counter)
{
    counter->cursor = 0;
    counter->count = 0;
    ResetEntryStates(counter);
}
