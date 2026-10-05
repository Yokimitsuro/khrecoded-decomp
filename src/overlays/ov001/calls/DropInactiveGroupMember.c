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
extern u32 IsGroupMemberActive(u32 groupId, int index);

void DropInactiveGroupMember(PartyMember *member)
{
    PartyState *party = data_ov001_020a04bc;

    if (member->memberIndex >= 0 && !IsGroupMemberActive(party->groupId, member->memberIndex)) {
        member->memberIndex = -1;
    }
}
