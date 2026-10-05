#include "nitro/types.h"

typedef struct RecordSlot {
    u8 pad_00[0xd];
    u8 enabled;
} RecordSlot;

extern RecordSlot *ActorSlot_GetByIndex(int index);

u8 GetRecordSlotEnabled(int index)
{
    RecordSlot *slot = ActorSlot_GetByIndex(index);

    if (slot == NULL) {
        return 0;
    }
    if (slot->enabled == 0) {
        return 0;
    }
    return slot->enabled;
}
