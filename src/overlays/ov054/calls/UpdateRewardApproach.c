#include "nitro/types.h"

typedef struct Actor Actor;

typedef struct ActorTimer {
    void (*handler)(Actor *actor);
    int delay;
} ActorTimer;

struct Actor {
    u8 pad_000[0x1f8];
    void (*onEvent)(Actor *actor, int event, int value);
    void (*onApproach)(Actor *actor, int speed);
    u8 pad_200[0x234 - 0x200];
    u32 inputFlags;
    u8 pad_238[0x75c - 0x238];
    int currentState;
    u8 pad_760[0x768 - 0x760];
    int isActive;
    u8 pad_76c[0x9b4 - 0x76c];
    u8 selection;
    u8 pad_9b5[0x9bc - 0x9b5];
    ActorTimer timer;
    int distance;
    u8 pad_9c8[0x10ec - 0x9c8];
    void (*setMode)(Actor *actor, int mode);
};

extern void *func_ov001_0206db78(u32 selection);
extern u16 SharedObject_GetId(void *self);
extern void func_ov054_020d34d0(Actor *actor, int arg);
extern BOOL IsLockedOnActiveFieldUnit(Actor *actor);
extern void UpdateRewardCharge(Actor *actor);

void UpdateRewardApproach(Actor *actor)
{
    u32 pressed = actor->inputFlags & 4;
    ActorTimer *timer = &actor->timer;

    if (SharedObject_GetId(func_ov001_0206db78(actor->selection)) == 0) {
        func_ov054_020d34d0(actor, 0);
    }
    if (pressed) {
        if (!IsLockedOnActiveFieldUnit(actor)) {
            if (actor->onEvent != NULL) {
                actor->onEvent(actor, 0x1e, -1);
            }
            timer->handler = UpdateRewardCharge;
            timer->delay = 0x19;
            return;
        }
        actor->setMode(actor, 3);
        return;
    }
    if (actor->isActive != 0 && actor->currentState == 0xc && actor->onApproach != NULL) {
        actor->onApproach(actor, 0xf000);
    }
    if (actor->distance >= 0x1e000) {
        actor->setMode(actor, 4);
    }
}
