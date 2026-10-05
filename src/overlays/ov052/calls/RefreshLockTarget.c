#include "nitro/types.h"

typedef struct {
    u8 pad0[0x10];
    int target;
    u8 pad14[0xb0];
    int lockMode;
} LockOnInfo;

typedef struct {
    int target;
} LockState;

typedef struct {
    u8 pad0[0x234];
    u32 flags;
    u8 pad238[0x3c];
    LockOnInfo lock;
    u8 pad33c[0xa10 - 0x33c];
    LockState state;
} Actor;

void RefreshLockTarget(Actor *actor)
{
    LockState *state = &actor->state;
    LockOnInfo *lock = &actor->lock;
    state->target = 0;
    if (lock->lockMode != 0 && (actor->flags & 4) && lock->lockMode == 1) {
        int target = lock->target;
        int owner = *(int *)(target + 0x14);
        if (owner != 0) {
            u8 kind = *(u8 *)(owner + 0x194);
            if (kind == 2 || kind == 4) {
                state->target = target;
            }
        }
    }
}
