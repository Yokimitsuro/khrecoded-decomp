#include "nitro/types.h"

typedef struct BufferSlot {
    u8 data[0x30];
} BufferSlot;

extern BOOL func_ov001_0206a918(BufferSlot *slot);

void BufferSlots_FreePair(BufferSlot *slots)
{
    int i;

    for (i = 0; i < 2; i++) {
        func_ov001_0206a918(&slots[i]);
    }
}
