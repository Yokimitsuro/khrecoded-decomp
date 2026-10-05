#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionQuery {
    VecFx32 *origin;
    VecFx32 *delta;
    int unk_08;
    u16 unk_0c;
    u16 layerMask;
    u32 filter;
    u8 pad_14[0x4c];
} CollisionQuery;

typedef struct CollisionHit {
    u32 unk_00;
    void *surface;
    u8 pad_08[0x24];
    fx32 fraction;
} CollisionHit;

typedef struct MovingBody {
    u8 pad_00[0x70];
    VecFx32 position;
    VecFx32 velocity;
    VecFx32 hitPoint;
    fx32 stepScale;
} MovingBody;

typedef struct CollisionOwner {
    u8 pad_000[0x130];
    u32 collisionFilter;
} CollisionOwner;

extern int FX_Mul(int left, int right);
extern CollisionHit *ResetAndQueryWorldCollision(CollisionQuery *query);
extern void AddScaledVector(fx32 scale, const VecFx32 *scaledVector, const VecFx32 *baseVector, VecFx32 *resultVector);

BOOL RaycastMoveStep(MovingBody *body, CollisionOwner *owner)
{
    VecFx32 origin;
    VecFx32 delta;
    CollisionQuery query;
    CollisionHit *hit;

    origin = body->position;
    delta.x = FX_Mul(body->velocity.x, body->stepScale);
    delta.y = FX_Mul(body->velocity.y, body->stepScale);
    delta.z = FX_Mul(body->velocity.z, body->stepScale);
    query.origin = &origin;
    query.delta = &delta;
    query.unk_08 = 0;
    query.unk_0c = 0;
    query.layerMask = 0x7f;
    query.filter = owner->collisionFilter;
    hit = ResetAndQueryWorldCollision(&query);
    if (hit == NULL) {
        return FALSE;
    }
    if (hit->surface == NULL) {
        return FALSE;
    }
    AddScaledVector(hit->fraction, &delta, &origin, &body->hitPoint);
    return TRUE;
}
