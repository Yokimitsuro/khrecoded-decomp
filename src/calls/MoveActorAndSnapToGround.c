#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct VecS16 {
    s16 x;
    s16 y;
    s16 z;
} VecS16;

typedef struct Surface {
    u8 pad_00[0x0d];
    u8 unk_0D;
    u8 pad_0E[0x06];
    VecS16 normal;
    u8 pad_1A[0x2e];
    fx32 unk_48;
} Surface;

typedef struct CollBox {
    VecFx32 max;
    VecFx32 min;
} CollBox;

typedef struct CollShape {
    void *geometry;
    CollBox box;
    s32 kind;
} CollShape;

typedef struct CollSweep {
    CollShape shape;
    VecFx32 delta;
    CollBox sweptBox;
} CollSweep;

typedef struct Capsule {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
    fx32 radius;
} Capsule;

typedef struct Sphere {
    VecFx32 center;
    fx32 radius;
} Sphere;

typedef struct ContactEntry {
    Surface *surface;
    s32 kind;
    u8 flags;
} ContactEntry;

typedef struct ContactSet {
    ContactEntry entries[16];
    VecFx32 normals[16];
    u8 entryCount;
    u8 order[32];
    u8 orderCount;
} ContactSet;

typedef struct HitResult {
    u32 pad_00;
    Surface *surface;
    u8 pad_08[0x24];
    VecFx32 velocity;
    u8 pad_38[0x80];
} HitResult;

typedef struct CollBody {
    u8 pad_000[0x119];
    u8 useSweptBox;
    u8 pad_11A[0x16];
    CollSweep sweep;
} CollBody;

typedef struct CollActor {
    CollBody *body;
    u32 flags;
    u8 pad_08[0x0c];
    fx32 unk_14;
    fx32 unk_18;
    fx32 unk_1C;
    VecFx32 unk_20;
    s32 unk_2C;
    u8 pad_30[0x08];
    s16 unk_38;
    u8 pad_3A[0x0a];
    HitResult lastHit;
    VecFx32 lastPos;
    s32 groundKind;
    u8 contactIndex;
    u8 pad_10D[0x07];
    ContactSet contacts;
    u8 pad_2B8[0x0c];
    CollBox cacheBox;
    u8 unk_2DC[0x80];
    u8 unk_35C[0x80];
    u8 unk_3DC[0x04];
} CollActor;

typedef struct HitContext {
    CollActor *actor;
    s32 pass;
    s32 aborted;
} HitContext;

typedef struct HitContextRef {
    HitContext *context;
    s32 count;
} HitContextRef;

typedef BOOL (*CollCallback)();

typedef struct Callback {
    CollCallback func;
    void *arg;
} Callback;

typedef struct ContactState {
    CollActor *actor;
    HitContext *context;
    VecFx32 floorNormal;
    VecFx32 wallNormal;
    VecFx32 ceilingNormal;
    void *world;
    u32 flags;
    s32 landed;
} ContactState;

typedef struct CollQuery {
    u8 pad_00[0x0c];
    u16 unk_0C;
    u16 unk_0E;
    CollBody *body;
    CollBox *cacheBox;
    void *unk_18;
    void *unk_1C;
    void *unk_20;
    CollSweep *sweep;
    ContactSet *contacts;
    s32 unk_2C;
    u8 pad_30[0x0c];
    u8 unk_3C;
    u8 unk_3D;
    u8 unk_3E;
    u8 pad_3F;
    u8 unk_40;
    u8 pad_41[3];
    HitContextRef *contextRef;
    s32 unk_48;
    u32 pad_4C;
    Callback onContact;
    Callback filter;
} CollQuery;

extern void *func_02036244(void);
extern void func_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern fx32 FX_Sqrt(u32 value);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern s64 _ll_mul(s64 a, s64 b);
extern void InitCapsuleShape(CollShape *out, Capsule *capsule, const VecFx32 *start, const VecFx32 *end,
                          const VecFx32 *direction, fx32 length, fx32 radius);
extern void func_0203ad28(CollShape *out, Sphere *sphere, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta(const CollBox *src, CollBox *dst, const VecFx32 *delta);
extern void RefreshActorMeshCache(void *world, CollActor *actor, CollQuery *query, CollSweep *sweep, VecFx32 *vel);
extern s32 func_ov001_02063a4c(void);
extern s32 func_ov001_02063a38(void);
extern VecFx32 *GetModeContext(void);
extern void func_02032000(ContactSet *set, const VecFx32 *normal);
extern void NegateVecFx32(VecFx32 *vec);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern HitResult *func_020351e0(void *world, CollQuery *query);
extern void func_ov059_020cd46c(void *world, CollActor *actor, CollQuery *query, HitResult *hit, VecFx32 *pos,
                                VecFx32 *vel, fx32 height, u32 flags);
extern void func_020382c4(void *world, CollActor *actor, CollQuery *query, HitResult *hit, VecFx32 *pos,
                          VecFx32 *vel, fx32 height, u32 flags, ContactState *state);
extern BOOL ClassifyCollisionContact();
extern BOOL ResolveSteepSurfaceContact();
extern BOOL Container_IsOperationAllowed();
extern const VecFx32 data_0205344c;

static inline BOOL IsMode4(void)
{
    return func_ov001_02063a38() == 4;
}

static inline BOOL IsMode7(void)
{
    return func_ov001_02063a38() == 7;
}

static inline BOOL IsGravityWorld(void)
{
    BOOL inMode;
    BOOL result = FALSE;
    if (func_ov001_02063a4c() >= 4 && func_ov001_02063a4c() <= 9) {
        inMode = TRUE;
        if (!IsMode4() && !IsMode7()) {
            inMode = FALSE;
        }
        if (inMode) {
            result = TRUE;
        }
    }
    return result;
}

static inline fx32 HorizontalLength(const VecFx32 *v)
{
    s64 z = v->z;
    s64 x = v->x;
    return FX_Sqrt((u32)((_ll_mul(x, x) + _ll_mul(z, z)) >> 12));
}

static inline VecFx32 VecS16ToFx32(const VecS16 *src)
{
    VecFx32 result;
    result.x = src->x;
    result.y = src->y;
    result.z = src->z;
    return result;
}

static inline BOOL HasGroundRef(u32 flags, CollActor *actor)
{
    return (flags & 4) && actor->lastHit.surface != NULL;
}

static inline fx32 MinFx(fx32 a, fx32 b)
{
    fx32 result = a;
    if (a > b) {
        result = b;
    }
    return result;
}

static inline fx32 MaxFx(fx32 a, fx32 b)
{
    fx32 result = a;
    if (a < b) {
        result = b;
    }
    return result;
}

static inline void InitCapsuleEnds(HitContext *context, VecFx32 *upper, VecFx32 *lower, VecFx32 base)
{
    context->aborted = 0;
    *upper = base;
    *lower = base;
}

static inline void SetSweepDelta(CollSweep *sweep, const VecFx32 *delta)
{
    sweep->delta = *delta;
    OffsetBoxByDelta(&sweep->shape.box, &sweep->sweptBox, &sweep->delta);
}

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

static inline VecFx32 VecAdd(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    func_01ff9e0c(a, b, &result);
    return result;
}

static inline VecFx32 VecRejectAxis(const VecFx32 *v, const VecFx32 *axis, fx32 dot)
{
    VecFx32 projection;
    VecFx32 scaled;
    VecFx32 result;
    scaled = *axis;
    ScaleVecFx32InPlace(&scaled, dot);
    projection = scaled;
    func_01ff9e3c(v, &projection, &result);
    return result;
}

static inline VecFx32 VecNegated(const VecFx32 *v)
{
    VecFx32 result = *v;
    NegateVecFx32(&result);
    return result;
}

static inline Callback MakeCallback(CollCallback func, void *arg)
{
    Callback result;
    result.func = func;
    result.arg = arg;
    return result;
}

static inline HitContextRef MakeContextRef(HitContext *context, s32 count)
{
    HitContextRef result;
    result.context = context;
    result.count = count;
    return result;
}

static inline ContactState MakeContactState(CollActor *actor, HitContext *context, void *world, u32 flags)
{
    ContactState result;
    result.actor = actor;
    result.context = context;
    result.world = world;
    result.flags = flags;
    result.landed = 0;
    return result;
}

static inline CollShape MakeCapsuleShape(Capsule *capsule, const VecFx32 *start, const VecFx32 *end, fx32 radius)
{
    CollShape shape;
    VecFx32 offset;
    VecFx32 direction;
    func_01ff9e3c(end, start, &offset);
    direction = offset;
    InitCapsuleShape(&shape, capsule, start, end, &direction, func_01ffaff4(&direction, &direction), radius);
    return shape;
}

static inline void InitProbeSweep(CollSweep *sweep, Sphere *sphere, VecFx32 *center, const VecFx32 *pos, fx32 y)
{
    VecFx32 origin;
    VecFx32 delta;
    origin.x = pos->x;
    origin.y = y;
    origin.z = pos->z;
    *center = origin;
    delta.x = 0;
    delta.y = -0x50000;
    delta.z = 0;
    func_0203ad28(&sweep->shape, sphere, center, 0xcd);
    SetSweepDelta(sweep, &delta);
}

void MoveActorAndSnapToGround(VecFx32 *pos, VecFx32 *vel, CollActor *actor, u32 flags)
{
    CollQuery query;
    CollSweep sweep;
    CollSweep capsuleSweep;
    CollSweep sphereSweep;
    VecFx32 appliedVel;
    HitContext hitContext;
    ContactState state;
    VecFx32 savedPos;
    VecFx32 savedVel;
    VecFx32 upper;
    VecFx32 lower;
    Capsule capsule;
    Sphere sphere;
    VecFx32 groundNormal;
    HitContextRef contextRef;
    ContactSet *contacts;
    void *world;
    HitResult *hit;
    CollBody *body;
    fx32 height;
    fx32 axisDot;
    fx32 distance;
    BOOL commit;

    world = func_02036244();
    state = MakeContactState(actor, &hitContext, world, flags);
    contextRef = MakeContextRef(&hitContext, 2);
    savedPos = *pos;
    savedVel = *vel;
    contacts = &actor->contacts;
    InitCapsuleEnds(&hitContext, &upper, &lower, MakeVec(pos->x, pos->y + 0x900, pos->z));
    body = actor->body;
    if (body->sweep.shape.kind == 3) {
        Capsule *bodyCapsule = body->sweep.shape.geometry;
        height = bodyCapsule->end.y - bodyCapsule->start.y;
    } else {
        CollBox *box = body->useSweptBox ? &body->sweep.sweptBox : &body->sweep.shape.box;
        height = box->max.y - box->min.y;
    }
    upper.y += height - 0x900;
    upper.y = MaxFx(upper.y, lower.y + 0x80);
    capsuleSweep.shape = MakeCapsuleShape(&capsule, &upper, &lower, 0x900);
    SetSweepDelta(&capsuleSweep, vel);
    sweep = capsuleSweep;

    query.unk_0C = 0;
    query.unk_0E = 0;
    query.unk_40 = 0x0f;
    query.body = actor->body;
    query.contextRef = &contextRef;
    query.unk_48 = 0;
    query.cacheBox = &actor->cacheBox;
    query.unk_18 = actor->unk_2DC;
    query.unk_1C = actor->unk_35C;
    query.unk_20 = actor->unk_3DC;
    RefreshActorMeshCache(world, actor, &query, &sweep, vel);
    contacts->entryCount = 0;
    contacts->orderCount = 0;

    if (IsGravityWorld()) {
        VecFx32 *gravity = GetModeContext();
        VecFx32 negGravity;
        func_02032000(contacts, gravity);
        negGravity = VecNegated(gravity);
        func_02032000(contacts, &negGravity);
    }

    hitContext.pass = 0;
    query.unk_3C = 0;
    query.unk_2C = 0x800;
    query.sweep = &sweep;
    query.unk_3D = 1;
    query.onContact = MakeCallback(ClassifyCollisionContact, &state);
    query.filter = MakeCallback(ResolveSteepSurfaceContact, &state);
    hitContext.actor = actor;
    query.contacts = contacts;
    hit = func_020351e0(world, &query);
    if (hit != NULL) {
        *vel = hit->velocity;
        if (contacts->orderCount != 0) {
            query.contextRef->context->pass = 1;
            query.unk_48 = 0;
            query.onContact.func = NULL;
            query.filter.func = NULL;
            if (func_ov001_02063a38() == 7) {
                func_ov059_020cd46c(world, actor, &query, hit, pos, vel, upper.y - pos->y, flags);
            } else {
                func_020382c4(world, actor, &query, hit, pos, vel, upper.y - pos->y, flags, &state);
            }
            query.contacts = contacts;
        }
        if (IsGravityWorld()) {
            VecFx32 *gravity = GetModeContext();
            axisDot = VEC_DotProduct(vel, gravity);
            *vel = VecRejectAxis(vel, gravity, axisDot);
        }
        appliedVel = *vel;
        func_01ff9e0c(pos, vel, pos);
        if (actor->flags & 4) {
            actor->lastPos = *pos;
            actor->lastHit = *hit;
            actor->unk_1C = 0;
            actor->unk_18 = 0;
            actor->unk_14 = 0;
            actor->flags &= ~0x80;
            if (state.floorNormal.y < 0x1000) {
                actor->flags |= 0x400;
            }
        }
        if ((actor->flags & 8) && state.ceilingNormal.y < 0x1000) {
            actor->flags |= 0x800;
        }
        RefreshActorMeshCache(world, actor, &query, &sweep, vel);
    } else {
        *vel = sweep.delta;
        func_01ff9e0c(pos, vel, pos);
        appliedVel = *vel;
    }

    if (hitContext.aborted != 0) {
        goto finish;
    }

    /* Probe downward with a small sphere to find ground. */
    {
        VecFx32 sphereCenter;
        InitProbeSweep(&sphereSweep, &sphere, &sphereCenter, pos, capsule.start.y + 0x7b3);
    }
    sweep = sphereSweep;
    actor->flags &= ~4;
    hitContext.pass = 2;
    query.unk_3D = 1;
    query.unk_3E = 0;
    query.unk_40 = 9;
    query.unk_3C = 1;
    query.onContact.func = Container_IsOperationAllowed;
    query.unk_48 = 0;
    query.filter.func = NULL;
    hit = func_020351e0(world, &query);
    if (hit == NULL) {
        goto finish;
    }

    groundNormal = (contacts->entries[contacts->entryCount - 1].kind == 4)
                       ? contacts->normals[contacts->entryCount - 1]
                       : VecS16ToFx32(&hit->surface->normal);
    sphere.center.y -= 0xcd;
    distance = 0;
    commit = TRUE;
    if (actor->unk_2C == (s32)0x80000000) {
        if (contacts->entries[contacts->entryCount - 1].kind == 4) {
            if (HasGroundRef(flags, actor)) {
                axisDot = MinFx(contacts->normals[contacts->entryCount - 1].y, actor->lastHit.surface->normal.y);
            } else {
                axisDot = contacts->normals[contacts->entryCount - 1].y;
            }
        } else {
            if (HasGroundRef(flags, actor)) {
                axisDot = MinFx(hit->surface->normal.y, actor->lastHit.surface->normal.y);
            } else {
                axisDot = hit->surface->normal.y;
            }
        }
        if (axisDot < 0x1000) {
            if (axisDot > 0x10) {
                distance = FX_Div(HorizontalLength(vel), axisDot);
            } else {
                distance = HorizontalLength(vel);
            }
        }
        distance += (vel->y < 0) ? -vel->y : vel->y;
        if ((flags & 4) && actor->lastHit.surface != NULL) {
            VecFx32 refNormal = VecS16ToFx32(&actor->lastHit.surface->normal);
            if (VEC_DotProduct(&groundNormal, &refNormal) > 0xff0) {
                distance += actor->unk_38;
            }
        }
    }
    if (contacts->entries[contacts->entryCount - 1].kind == 4 &&
        contacts->entries[contacts->entryCount - 1].surface->unk_0D != 0) {
        fx32 extra = contacts->entries[contacts->entryCount - 1].surface->unk_48;
        distance += (extra < 0) ? -extra : extra;
    }
    distance += 0x10;
    if (sphere.center.y >= pos->y - distance) {
        if (IsMode7() && pos->y < -0x80) {
            actor->flags |= 0x2000;
        }
        if (actor->flags & 0x2000) {
            vel->y = savedVel.y;
            *pos = VecAdd(&savedPos, vel);
            actor->flags &= ~4;
            commit = FALSE;
            actor->groundKind = 0;
        } else {
            actor->flags |= 4;
            actor->unk_2C = 0x80000000;
            actor->unk_1C = 0;
            actor->unk_18 = 0;
            actor->unk_14 = 0;
            appliedVel.y += sphere.center.y - pos->y;
            if (contacts->orderCount == 0 || vel->y != 0) {
                BOOL snap = TRUE;
                if (pos->y < sphere.center.y) {
                    s32 i;
                    s32 count = contacts->entryCount;
                    for (i = 0; i < count; i++) {
                        if (contacts->normals[i].y < -0x80) {
                            snap = FALSE;
                            sphere.center.y = pos->y;
                            break;
                        }
                    }
                }
                if (snap) {
                    pos->y = sphere.center.y;
                }
            }
            actor->unk_20 = data_0205344c;
            if (contacts->normals[contacts->entryCount - 1].y < 0x1000) {
                actor->flags |= 0x400;
            }
        }
    } else {
        actor->flags &= ~0x2000;
    }
    if (commit) {
        actor->lastPos.x = pos->x;
        actor->lastPos.y = sphere.center.y;
        actor->lastPos.z = pos->z;
        actor->groundKind = (contacts->entries[contacts->entryCount - 1].kind == 4) ? 1 : 2;
        actor->lastHit = *hit;
        actor->contactIndex = contacts->entryCount - 1;
    }

finish:
    SetSweepDelta(&actor->body->sweep, &appliedVel);
    actor->body->useSweptBox = 0;
}
