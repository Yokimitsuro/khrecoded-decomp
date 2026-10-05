#include "nitro/types.h"

typedef struct GroupMember {
    u8 pad_000[0x1d0];
    u16 linkType;
    u16 linkedEventId;
} GroupMember;

u16 GetLinkedEventId(GroupMember *member)
{
    u16 eventId;

    if (member == NULL) {
        return 0;
    }
    if (member->linkType != 1) {
        return 0;
    }
    eventId = member->linkedEventId;
    if (eventId == 0) {
        return 0;
    }
    return eventId;
}
