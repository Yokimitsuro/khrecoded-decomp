#include "nitro/types.h"

typedef struct PartyState {
    u8 pad_00[0xb6];
    s16 groupId;
} PartyState;

typedef struct PartyMember {
    u8 pad_00[0x10];
    int memberIndex;
} PartyMember;

extern PartyState *data_ov001_020a04bc;
extern u32 func_ov021_020a8d3c(u32 groupId, int index);

void DropInactiveGroupMember(PartyMember *member)
{
    PartyState *party = data_ov001_020a04bc;

    if (member->memberIndex >= 0 && !func_ov021_020a8d3c(party->groupId, member->memberIndex)) {
        member->memberIndex = -1;
    }
}
