#include "nitro/types.h"

typedef struct {
    u8 pad0[0x34];
    int hitTimer;
    int flashTimer;
} TimerBlock;

typedef struct {
    u8 pad0[0xc4];
    int cooldown;
} LockTimers;

typedef struct {
    u8 pad0[0x9ec];
    int step;
    u8 pad9f0[8];
    int invincibleTimer;
    u8 pad9fc[0x14];
    TimerBlock timers;
    u8 pada4c[8];
    LockTimers lock;
} Actor;

void TickActorTimers(Actor *actor)
{
    TimerBlock *timers;
    LockTimers *lock;
    if (actor->invincibleTimer > 0) {
        actor->invincibleTimer -= actor->step;
        if (actor->invincibleTimer <= 0) {
            actor->invincibleTimer = 0;
        }
    }
    lock = &actor->lock;
    if (lock->cooldown > 0) {
        lock->cooldown -= actor->step;
        if (lock->cooldown <= 0) {
            lock->cooldown = 0;
        }
    }
    timers = &actor->timers;
    if (timers->hitTimer > 0) {
        timers->hitTimer -= actor->step;
        if (timers->hitTimer <= 0) {
            timers->hitTimer = 0;
        }
    }
    if (timers->flashTimer > 0) {
        timers->flashTimer -= actor->step;
        if (timers->flashTimer <= 0) {
            timers->flashTimer = 0;
        }
    }
}
