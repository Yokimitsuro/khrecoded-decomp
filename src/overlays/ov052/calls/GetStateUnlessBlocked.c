#include "nitro/types.h"

typedef struct {
    u8 pad0[0x1dc];
    int state;
    u8 pad1e0[0x9ac - 0x1e0];
    u64 flags;
    u8 pad9b4[0xc];
    int action;
} Actor;

int GetStateUnlessBlocked(Actor *actor)
{
    int result = actor->state;
    if ((actor->flags & 0x60020) != 0) {
        return 0;
    }
    if (actor->action == 0x18) {
        result = 0;
    }
    return result;
}
