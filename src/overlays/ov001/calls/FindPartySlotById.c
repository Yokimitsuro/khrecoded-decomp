#include "nitro/types.h"

typedef struct PartySlot {
    u16 pad_00;
    u16 memberId;
} PartySlot;

extern PartySlot *func_ov001_0209c1fc(u32 slot);

PartySlot *FindPartySlotById(u32 memberId)
{
    int i;
    PartySlot *slot;

    for (i = 0; i < 3; i++) {
        slot = func_ov001_0209c1fc((u16)i);
        if (slot != NULL && slot->memberId != 0 && slot->memberId == memberId) {
            return slot;
        }
    }
    return NULL;
}
