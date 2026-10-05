#include "nitro/types.h"

typedef void (*StateCallback)(void *entity, int state);
typedef void (*EndCallback)(void *entity, int arg, int value);

typedef struct {
    u8 pad0[0x1f8];
    EndCallback onEnd;
    u8 pad1fc[0x760 - 0x1fc];
    int frame;
    u8 pad764[4];
    int pending;
    u8 pad76c[0x9ac - 0x76c];
    u64 flags;
    u8 pad9b4[0x10ec - 0x9b4];
    StateCallback setState;
} Actor;

extern BOOL func_ov052_020c8730(Actor *actor);

void UpdateEndOfAction(Actor *actor)
{
    if ((actor->flags & 8) != 0) {
        actor->setState(actor, 9);
        return;
    }
    if ((actor->frame < 0x8000 || !func_ov052_020c8730(actor)) && actor->pending != 0) {
        actor->setState(actor, 1);
        if (actor->onEnd != NULL) {
            actor->onEnd(actor, 0, -1);
        }
    }
}
