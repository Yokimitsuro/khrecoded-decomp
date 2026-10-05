#include "nitro/types.h"

typedef struct PartyState {
    u8 pad_00[0x28];
    u16 flags;
} PartyState;

extern PartyState *data_ov001_020a04bc;
extern u32 GetBoundedEntryField(int index);

BOOL IsLeaderFlag3Active(void)
{
    PartyState *party = data_ov001_020a04bc;
    BOOL result = FALSE;

    if (party == NULL) {
        return result;
    }
    if (GetBoundedEntryField(0) != 0 && (party->flags & 8) > 0) {
        result = TRUE;
    }
    return result;
}
