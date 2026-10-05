#include "nitro/types.h"

typedef struct Actor {
    u8 pad_00[4];
    void *pool;
    u8 pad_08[0x54];
    s16 prevIndex;
} Actor;

extern BOOL IsDestroyed(Actor *self);
extern Actor *func_ov001_02086384(void *pool, int index);

static inline Actor *GetPrevLink(Actor *actor)
{
    return func_ov001_02086384(actor->pool, actor->prevIndex);
}

Actor *FindLivePrevLink(Actor *actor)
{
    while (actor->prevIndex >= 0) {
        actor = GetPrevLink(actor);
        if (!IsDestroyed(actor)) {
            return actor;
        }
    }
    return NULL;
}
