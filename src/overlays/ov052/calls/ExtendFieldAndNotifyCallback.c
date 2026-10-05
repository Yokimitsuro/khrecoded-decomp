#include "nitro/types.h"

typedef struct Actor {
    u8 pad_000[0x768];
    s32 notifyFlag;
    u8 pad_76c[0x260];
    s32 counter;
    u8 pad_9d0[0x71c];
    void (*callback)(struct Actor *self, int arg);
} Actor;

extern void ExtendIfGreater(int entity, int minValue);

/* Raises a floor value and notifies via callback */
void ExtendFieldAndNotifyCallback(Actor *actor)
{
    ExtendIfGreater((int)actor, 0x6000);
    if (actor->counter < 0) {
        actor->counter = 0;
    }
    if (actor->notifyFlag != 0) {
        actor->callback(actor, 4);
    }
}
