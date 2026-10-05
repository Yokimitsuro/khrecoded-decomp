#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef void (*ActorChangeStateFunc)(Actor *actor, s32 state);

struct Actor {
    u8 pad_0000[0x234];
    u32 collisionFlags;
    u8 pad_0238[0x768 - 0x238];
    BOOL animationEnded;
    u8 pad_076C[0x930 - 0x76c];
    u8 playerIndex;
    u8 pad_0931[0x948 - 0x931];
    fx32 elapsedTime;
    u8 pad_094C[0x970 - 0x94c];
    VecFx32 velocity;
    u8 pad_097C[0x1808 - 0x97c];
    ActorChangeStateFunc changeState;
};

extern const VecFx32 data_0205344c;
extern void *func_ov001_0206db78(u32 playerIndex);
extern void func_ov059_020c999c(Actor *actor);
extern void func_ov059_020ca35c(Actor *actor, s32 arg1, s32 arg2);
extern BOOL HasFlagsAt0xc(void *record, u16 mask);
extern BOOL func_ov021_020a7524(void *record);
extern BOOL func_ov059_020cb930(Actor *actor);

void Actor_UpdateSettleState(Actor *actor)
{
    void *record = func_ov001_0206db78(actor->playerIndex);
    u32 onGround = actor->collisionFlags & 4;

    func_ov059_020c999c(actor);
    if (!(actor->collisionFlags & 4)) {
        func_ov059_020ca35c(actor, 0, 0);
    } else {
        actor->velocity = data_0205344c;
    }
    if (actor->elapsedTime >= 0xf000 && onGround && HasFlagsAt0xc(record, 0x800) &&
        func_ov021_020a7524(record) && func_ov059_020cb930(actor)) {
        actor->changeState(actor, 5);
        return;
    }
    if (actor->animationEnded) {
        if (onGround) {
            actor->changeState(actor, 1);
        } else {
            actor->changeState(actor, 3);
        }
    }
}
