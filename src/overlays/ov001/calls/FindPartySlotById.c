#include "nitro/types.h"

typedef struct PartySlot {
    u16 pad_00;
    u16 memberId;
} PartySlot;

extern PartySlot *GetStagePartySlot(u32 slot);

PartySlot *FindPartySlotById(u32 memberId)
{
    int i;
    PartySlot *slot;

    for (i = 0; i < 3; i++) {
        slot = GetStagePartySlot((u16)i);
        if (slot != NULL && slot->memberId != 0 && slot->memberId == memberId) {
            return slot;
        }
    }
    return NULL;
}
