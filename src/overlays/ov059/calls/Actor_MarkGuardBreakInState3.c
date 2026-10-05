#include "nitro/types.h"

typedef struct Actor Actor;
typedef int (*StateGetter)(Actor *actor);

struct Actor {
    u8 pad_0000[0x1dc];
    int state;
    u8 pad_01e0[0x22c - 0x1e0];
    StateGetter getState;
    u8 pad_0230[0x16f8 - 0x230];
    u8 guardFlags;
};

static inline int GetActorState(Actor *actor)
{
    if (actor->getState != NULL) {
        return actor->getState(actor);
    }
    return actor->state;
}

void Actor_MarkGuardBreakInState3(Actor *actor)
{
    if (GetActorState(actor) == 3 && (actor->guardFlags & 0x10)) {
        actor->guardFlags |= 0x20;
    }
}
