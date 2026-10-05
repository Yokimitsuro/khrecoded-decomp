#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef void (*ActorCallback)(Actor *actor, int arg);

struct Actor {
    u8 pad_000[0x1fc];
    ActorCallback onLand;
    u8 pad_200[0x234 - 0x200];
    u32 state;
    u8 pad_238[0x760 - 0x238];
    s32 frame;
    u8 pad_764[0x768 - 0x764];
    s32 finished;
    u8 pad_76c[0x928 - 0x76c];
    u64 flags;
    u8 playerIndex;
    u8 pad_931[0x970 - 0x931];
    VecFx32 velocity;
    VecFx32 position;
    u8 pad_988[0x1800 - 0x988];
    s32 targetId;
    u8 pad_1804[0x1808 - 0x1804];
    ActorCallback onFinish;
};

extern const VecFx32 data_0205344c;
extern void func_ov059_020c999c(Actor *actor);
extern void Actor_GetRootMotionDelta(Actor *actor, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void *func_ov001_0206db78(u32 playerIndex);
extern s32 SharedObject_GetMode(void *obj);

void Actor_UpdateRootMotionJump(Actor *actor)
{
    VecFx32 delta;
    u32 locked = actor->state & 4;

    func_ov059_020c999c(actor);
    Actor_GetRootMotionDelta(actor, &delta);
    if (!locked) {
        if (delta.y != 0) {
            actor->velocity.y = delta.y;
        }
    } else {
        actor->velocity = data_0205344c;
    }
    VEC_Add(&actor->position, &delta, &actor->position);
    if (actor->frame >= 0x9000 && !(actor->flags & 0x2000)) {
        actor->flags |= 0x2000;
    }
    if (actor->finished == 0 && actor->frame >= 0xf000 && actor->frame < 0x15000) {
        if (actor->targetId == SharedObject_GetMode(func_ov001_0206db78(actor->playerIndex))) {
            if (actor->onLand) {
                actor->onLand(actor, 0x9000);
            }
            actor->flags &= ~(u64)0x2000;
        }
    }
    if (actor->finished != 0) {
        actor->flags &= ~(u64)0x2000;
        if (locked) {
            actor->onFinish(actor, 1);
            return;
        }
        actor->flags |= 0x100;
        actor->onFinish(actor, 3);
    }
}
