#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x124];
    u8 slotId;
    u8 pad_125[0x4d];
    s16 altSlotId;
} SlotOwner;

BOOL MatchesEitherSlotId(SlotOwner *owner, int slotId) {
    BOOL matches = FALSE;

    if (slotId == owner->altSlotId) {
        matches = TRUE;
    }
    if (owner->slotId == slotId) {
        matches = TRUE;
    }
    return matches;
}
