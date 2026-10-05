#include "nitro/types.h"

typedef struct Actor {
    u8 pad_00[0x52];
    u8 kind;
} Actor;

extern BOOL IsDestroyed(Actor *self);
extern Actor *FindFirstLiveLink(Actor *actor);
extern Actor *FindLiveNextLink(Actor *actor);

BOOL IsLeadLink(Actor *self)
{
    Actor *entry;
    Actor *lead;
    BOOL found;

    if (!IsDestroyed(self)) {
        entry = FindFirstLiveLink(self);
        lead = entry;
        found = FALSE;
        while (entry != NULL) {
            u8 kind = entry->kind;
            if (kind == 1 || kind == 10) {
                lead = entry;
                break;
            }
            if (!found && kind != 2) {
                found = TRUE;
                lead = entry;
            }
            entry = FindLiveNextLink(entry);
        }
        if (lead == self) {
            return TRUE;
        }
    }
    return FALSE;
}
