#include "nitro/types.h"

typedef struct Actor {
    u8 pad_0000[0x928];
    u64 stateFlags;
} Actor;

extern void ProbeLinkedMeshEntries(Actor *actor);
extern int func_ov059_020cb92c(Actor *actor);

void Actor_ProbeLinkIfFlagClear(Actor *actor)
{
    if ((actor->stateFlags & 0x800) == 0) {
        ProbeLinkedMeshEntries(actor);
        func_ov059_020cb92c(actor);
    }
}
