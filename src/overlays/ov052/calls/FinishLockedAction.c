#include "nitro/types.h"

typedef void (*StateCallback)(void *actor, int state);
typedef void (*EndCallback)(void *actor, int arg, int value);

typedef struct {
    u8 pad0[0x34];
} TimerBlock;

typedef struct {
    u8 pad0[0x1f8];
    EndCallback onEnd;
    u8 pad1fc[0x38];
    u32 lockFlags;
    u8 pad238[0x768 - 0x238];
    int pending;
    u8 pad76c[0x9b4 - 0x76c];
    u8 entryId;
    u8 pad9b5[0xf];
    int power;
    u8 pad9c8[0x30];
    int invincibleTimer;
    u8 pad9fc[0x14];
    TimerBlock timers;
    u8 pada44[0x10ec - 0xa44];
    StateCallback setState;
} Actor;

extern u32 func_ov001_0206db78(u32 index);
extern BOOL SelectGroundAction(Actor *actor, TimerBlock *timers);

void FinishLockedAction(Actor *actor)
{
    TimerBlock *timers = &actor->timers;
    u32 locking;
    func_ov001_0206db78(actor->entryId);
    locking = actor->lockFlags & 4;
    if (actor->power >= 0x10000 && locking) {
        int saved = actor->invincibleTimer;
        actor->invincibleTimer = 0;
        if (SelectGroundAction(actor, timers)) {
            return;
        }
        actor->invincibleTimer = saved;
    }
    if (actor->pending != 0) {
        if (locking) {
            actor->setState(actor, 1);
            if (actor->onEnd != NULL) {
                actor->onEnd(actor, 0, -1);
            }
        } else {
            actor->setState(actor, 4);
        }
    }
}
