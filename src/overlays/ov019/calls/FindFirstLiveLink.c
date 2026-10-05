#include "nitro/types.h"

typedef struct Actor {
    u8 pad_00[4];
    void *pool;
    u8 pad_08[0x52];
    u16 flags;
    s16 prevIndex;
} Actor;

extern BOOL IsDestroyed(Actor *self);
extern Actor *func_ov001_02086384(void *pool, int index);

Actor *FindFirstLiveLink(Actor *actor)
{
    Actor *result = NULL;
    while (1) {
        if (!IsDestroyed(actor)) {
            result = actor;
        }
        if (actor->prevIndex < 0) {
            break;
        }
        actor = func_ov001_02086384(actor->pool, actor->prevIndex);
    }
    return result;
}
