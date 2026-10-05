#include "nitro/types.h"

typedef struct Ov081State {
    u8 pad_00[0x6120];
    void *entries[110];
    u8 slotEntryIndices[16];
} Ov081State;

extern Ov081State *data_ov081_020c5da0;

void *GetSlotEntry(int slot)
{
    return data_ov081_020c5da0->entries[data_ov081_020c5da0->slotEntryIndices[slot]];
}
