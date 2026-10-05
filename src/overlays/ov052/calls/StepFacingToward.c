#include "nitro/types.h"

typedef struct {
    u8 pad0[0x1c];
    u16 turnLimit;
} TimerBlock;

typedef struct {
    u8 pad0[0x234];
    u32 lockFlags;
    u8 pad238[0x9c0 - 0x238];
    int action;
    u8 pad9c4[0x38];
    u16 facing;
    u8 pad9fe[0x12];
    TimerBlock timers;
} Actor;

extern s32 func_ov001_02063a38(void);

int StepFacingToward(Actor *actor, int target)
{
    TimerBlock *timers = &actor->timers;
    int current = actor->facing;
    BOOL force = FALSE;
    int diff;
    int distance;
    int limit;
    if (target == current) {
        return target;
    }
    diff = (u16)(target - current);
    limit = timers->turnLimit;
    if (diff > 0x8000) {
        distance = (u16)(0x10000 - diff);
    } else {
        distance = diff;
    }
    if (distance <= limit) {
        return target;
    }
    if (actor->lockFlags & 4) {
        force = TRUE;
    } else if (func_ov001_02063a38() == 4 && actor->action != 0x11) {
        force = TRUE;
    }
    if (force && distance > 0) {
        return target;
    }
    if (diff >= 0x8000) {
        limit = -limit;
    }
    return (u16)(current + limit);
}
