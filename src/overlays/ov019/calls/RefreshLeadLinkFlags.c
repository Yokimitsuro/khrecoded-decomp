#include "nitro/types.h"

typedef struct Actor {
    u8 pad_00[0x4f];
    u8 unkBits : 6;
    u8 isLead : 1;
    u8 unkBit7 : 1;
} Actor;

extern Actor *FindFirstLiveLink(Actor *actor);
extern Actor *FindLiveNextLink(Actor *actor);
extern BOOL IsLeadLink(Actor *self);

void RefreshLeadLinkFlags(Actor *actor)
{
    Actor *entry = FindFirstLiveLink(actor);
    if (entry == NULL) {
        entry = FindLiveNextLink(actor);
    }
    if (entry == NULL) {
        return;
    }
    do {
        entry->isLead = IsLeadLink(entry) ? TRUE : FALSE;
        entry = FindLiveNextLink(entry);
    } while (entry != NULL);
}
