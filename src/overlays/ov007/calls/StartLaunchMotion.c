#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 active : 1;
    u8 airborne : 1;
    u8 flagsHigh : 6;
    u8 phase;
    u16 timer;
    VecFx32 origin;
    fx32 velocityX;
    fx32 gravity;
    fx32 velocityZ;
} LaunchMotion;

typedef struct {
    u8 pad_00[0x58];
    VecFx32 position;
    u8 pad_64[0x24];
    LaunchMotion motion;
    u8 pad_A4[8];
    s16 heading;
    u8 facing;
    u8 state;
} LaunchActor;

void StartLaunchMotion(LaunchActor *actor, const VecFx32 *velocity) {
    s16 heading = actor->heading;
    u8 facing = actor->facing;
    LaunchMotion *motion = &actor->motion;

    actor->motion.active = TRUE;
    actor->motion.airborne = TRUE;
    motion->phase = 0;
    motion->timer = 0;
    motion->origin = actor->position;
    motion->gravity = 0x300;
    motion->velocityX = velocity->x;
    motion->velocityZ = velocity->z;
    actor->heading = heading;
    actor->facing = facing;
    actor->state = 4;
}
