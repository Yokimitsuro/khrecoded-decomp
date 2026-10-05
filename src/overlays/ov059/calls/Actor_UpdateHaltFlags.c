#include "nitro/types.h"

struct Actor;
typedef void (*ActorEventFunc)(struct Actor *actor, int event);

typedef struct {
    s32 kind : 8;
    s32 extra : 24;
} ActorState;

typedef struct Actor {
    u8 pad_0000[0x1fc];
    ActorEventFunc onHalt;
    u8 pad_0200[0x234 - 0x200];
    u32 bodyFlags;
    u8 pad_0238[0x760 - 0x238];
    s32 targetIndex;
    u8 pad_0764[0x768 - 0x764];
    s32 landed;
    u8 pad_076c[0x928 - 0x76c];
    u64 flags;
    u8 pad_0930[0x934 - 0x930];
    ActorState state;
    u8 pad_0938[0x1808 - 0x938];
    ActorEventFunc onStep;
} Actor;

extern void func_ov059_020caec0(Actor *actor);
extern void func_ov059_020c999c(Actor *actor);
extern void func_ov059_020c93f8(Actor *actor);

void Actor_UpdateHaltFlags(Actor *actor)
{
    if (actor->targetIndex >= 0 && !(actor->flags & 0x2000)) {
        func_ov059_020caec0(actor);
        if (actor->onHalt != NULL) {
            actor->onHalt(actor, 0);
        }
        actor->flags |= 0x2000;
        if (actor->state.kind == 3) {
            actor->state.kind = 4;
        }
    }
    if (actor->landed != 0) {
        u32 grounded = actor->bodyFlags & 4;
        actor->flags &= ~0x2000;
        if (grounded) {
            actor->onStep(actor, 1);
        } else {
            actor->flags |= 0x100;
            actor->onStep(actor, 3);
        }
        if (actor->state.kind != 1 && actor->state.kind != 2) {
            actor->state.kind = 0;
        }
    }
    func_ov059_020c999c(actor);
    func_ov059_020c93f8(actor);
}
