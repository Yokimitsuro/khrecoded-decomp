#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct NNSG3dResMdl NNSG3dResMdl;

typedef struct ShadowVolume {
    VecFx32 position;
    fx32 scale;
    NNSG3dResMdl **modelRef;
    u8 alpha;
    u8 pad_15;
    u16 rotY;
} ShadowVolume;

typedef struct RiderState {
    u8 pad_000[0x194];
    u8 mode;
} RiderState;

typedef struct RiderLink {
    u8 pad_00[0x14];
    RiderState *state;
} RiderLink;

typedef struct ActorPhysics {
    u8 pad_00[0x10];
    RiderLink *link;
    u8 pad_14[0xbc - 0x14];
    fx32 groundY;
    u8 pad_c0[0xc4 - 0xc0];
    BOOL onGround;
} ActorPhysics;

typedef struct Actor {
    u8 pad_000[0x274];
    ActorPhysics physics;
    u8 pad_33c[0x694 - 0x33c];
    ShadowVolume shadow;
    VecFx32 shadowOffset;
} Actor;

extern VecFx32 *Actor_GetModelPosition(Actor *actor);
extern u16 GetLinkedAngleOffset_020cd104(Actor *actor);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void ShadowVolume_Draw(ShadowVolume *shadow);

void Actor_DrawGroundShadow(Actor *actor) {
    ActorPhysics *physics = &actor->physics;
    VecFx32 pos;

    if (physics->onGround == 0) {
        return;
    }
    if (physics->link != NULL) {
        u8 mode = physics->link->state->mode;
        if (mode != 2 && mode != 4) {
            return;
        }
    }
    pos = *Actor_GetModelPosition(actor);
    pos.y = physics->groundY;
    if (Actor_GetModelPosition(actor)->y > pos.y + 0x8000) {
        return;
    }
    if (actor->shadowOffset.x != 0 || actor->shadowOffset.y != 0 || actor->shadowOffset.z != 0) {
        VEC_Add(&pos, &actor->shadowOffset, &pos);
    }
    actor->shadow.position = pos;
    actor->shadow.rotY = GetLinkedAngleOffset_020cd104(actor);
    ShadowVolume_Draw(&actor->shadow);
}
