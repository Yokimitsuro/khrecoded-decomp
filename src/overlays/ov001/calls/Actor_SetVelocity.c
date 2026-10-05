#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MovementBody {
    u8 pad_00[0x8];
    VecFx32 velocity;
} MovementBody;

typedef struct Actor {
    u8 pad_000[0x84c];
    VecFx32 velocity;
    u8 pad_858[0xd18 - 0x858];
    MovementBody *body;
    u8 pad_d1c[0xef4 - 0xd1c];
    u32 flags;
    s32 targetAngle;
    s32 angle;
} Actor;

extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern u16 FX_Atan2Idx(int vertical, int horizontal);
extern fx32 VEC_Mag(const VecFx32 *v);

void Actor_SetVelocity(Actor *actor, const VecFx32 *velocity)
{
    VecFx32 planar;
    VecFx32 direction;
    MovementBody *body;

    if (velocity == NULL) {
        actor->velocity.x = 0;
        actor->velocity.y = 0;
        actor->velocity.z = 0;
    } else {
        actor->velocity = *velocity;
        if (actor->flags & 4) {
            VEC_Normalize(&actor->velocity, &direction);
            actor->angle = (u16)(0x13fff - FX_Atan2Idx(direction.z, direction.x));
        }
    }
    planar = actor->velocity;
    if (VEC_Mag(&planar) <= 0x10) {
        planar.x = planar.y = planar.z = 0;
    }
    body = actor->body;
    body->velocity.x = planar.x;
    body->velocity.y = 0;
    body->velocity.z = planar.z;
}
