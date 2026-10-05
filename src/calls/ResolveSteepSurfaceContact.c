#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Surface {
    u8 pad_00[0x40];
    s32 unk_40;
} Surface;

typedef struct SurfaceRef {
    Surface *surface;
    s32 kind;
    u8 flags;
} SurfaceRef;

typedef struct ContactPlane {
    s32 distance;
    VecFx32 normal;
    s32 time;
    u8 surfaceType;
} ContactPlane;

typedef struct Body {
    u32 pad_00;
    u32 flags;
    u8 pad_08[0x0c];
    VecFx32 push;
    VecFx32 velocity;
    s32 unk_2C;
} Body;

typedef struct ContactState {
    Body *body;
    VecFx32 *expected;
    u8 pad_08[0x28];
    u32 flags;
} ContactState;

typedef struct CollSegment {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
} CollSegment;

typedef struct Capsule {
    CollSegment segment;
    fx32 radius;
} Capsule;

typedef struct CollShape {
    Capsule *capsule;
    fx32 box[6];
    s32 kind;
} CollShape;

typedef struct Mover {
    CollShape shape;
    VecFx32 velocity;
} Mover;

typedef struct StageEntry {
    u8 pad_00[0x9c0];
    s32 unk_9C0;
} StageEntry;

typedef struct Actor {
    u8 pad_00[0x180];
    u8 unk_180;
} Actor;

typedef struct PlanarVec {
    fx32 x;
    fx32 z;
} PlanarVec;

extern s16 data_02053800[];
extern s16 data_020539c0[];
extern s16 data_02053640[];

extern s32 func_ov001_02063a38(void);
extern StageEntry *func_ov001_0206db5c(int index);
extern BOOL AreWallNormalsEnclosing(Actor *actor, s32 limit);
extern void func_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);
extern fx32 FX_Sqrt(u32 value);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void NormalizeXy(PlanarVec *vec);
extern void SafeNormalizeXy(PlanarVec *vec);
extern fx32 ComputeOneMinusSquareFraction(fx32 value);
extern void ScalePairInPlace(PlanarVec *pair, fx32 scale);
extern fx32 Surface_GetKindValue(Surface *surface);
extern s64 _ll_mul(s64 a, s64 b);
extern fx32 FX_Mul(fx32 left, fx32 right);
extern void InitSegmentFromEndpoints(CollSegment *segment);
extern void SetShapePosition(CollShape *shape, const VecFx32 *pos);
extern BOOL TestShapeAgainstEntry(CollShape *shape, SurfaceRef *ref, ContactPlane *contact);

static inline s32 Clamp(s32 value, s32 lo, s32 hi)
{
    return value > hi ? hi : (value < lo ? lo : value);
}

static inline BOOL IsMode7(void)
{
    return func_ov001_02063a38() == 7;
}

static inline VecFx32 CrossUp(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 cross;
    cross.x = -(fx32)((_ll_mul(a->z, b->y) + 0x800) >> 12);
    cross.y = 0;
    cross.z = (fx32)((_ll_mul(a->x, b->y) + 0x800) >> 12);
    return cross;
}

static inline VecFx32 VecCross(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    func_01ff9ea8(a, b, &result);
    return result;
}

static inline VecFx32 VecAdd(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    func_01ff9e0c(a, b, &result);
    return result;
}

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

static inline void PlaceShape(CollShape *shape, VecFx32 pos)
{
    SetShapePosition(shape, &pos);
}

static inline PlanarVec GetPlanar(const VecFx32 *v)
{
    PlanarVec result;
    result.x = v->x;
    result.z = v->z;
    return result;
}

void ResolveSteepSurfaceContact(SurfaceRef *ref, VecFx32 *normal, ContactState *state, Actor *actor,
                                         Mover *mover)
{
    VecFx32 tangent;
    ContactPlane contact;
    CollShape shape;
    Capsule capsule;
    VecFx32 upAxis;
    PlanarVec slopeDir;
    PlanarVec pushDir;
    Body *body;
    fx32 speed;
    fx32 pushMag;
    s32 stageKind;

    if (ref->flags & 3) {
        body = state->body;
        if (state->expected->z != 0) {
            return;
        }
        if (mover->velocity.y <= 0 && !IsMode7() && body->velocity.x == 0 && body->velocity.y == 0 &&
            body->velocity.z == 0) {
            stageKind = func_ov001_0206db5c(0)->unk_9C0;
            if ((state->flags & 4) == 0 &&
                ((stageKind >= 2 && stageKind <= 4) || (stageKind >= 10 && stageKind <= 13) ||
                 (stageKind >= 21 && stageKind <= 22) || (stageKind >= 25 && stageKind <= 27)) &&
                normal->y > 0 && (ref->flags & 3) && actor->unk_180 >= 2) {
                s32 limit;
                if (ref->kind == 4 && (ref->surface->unk_40 == 0 || ref->surface->unk_40 == 3)) {
                    limit = 0x10;
                } else {
                    limit = data_02053800[0x15];
                }
                if (AreWallNormalsEnclosing(actor, limit)) {
                    upAxis = MakeVec(0, 0x1000, 0);
                    tangent = CrossUp(normal, &upAxis);
                    body->velocity = VecCross(&tangent, normal);
                    body->velocity.y = Clamp(body->velocity.y, data_02053640[0x11], data_020539c0[0x18]);
                    slopeDir = GetPlanar(&body->velocity);
                    NormalizeXy(&slopeDir);
                    ScalePairInPlace(&slopeDir,
                                              ComputeOneMinusSquareFraction(body->velocity.y));
                    body->velocity.x = slopeDir.x;
                    body->velocity.z = slopeDir.z;
                    if (ref->kind == 4 && ref->surface->unk_40 != 1) {
                        speed = FX_Mul(Surface_GetKindValue(ref->surface), 0x1333);
                        speed = Clamp(speed, 0x4cd, 0x666);
                        func_01ffaff4(&body->velocity, &body->velocity);
                        ScaleVecFx32InPlace(&body->velocity, speed);
                    } else {
                        func_01ffaff4(&body->velocity, &body->velocity);
                        ScaleVecFx32InPlace(&body->velocity, 0x4cd);
                    }
                    body->unk_2C = 0;
                    return;
                }
            }

            shape = mover->shape;
            capsule = *mover->shape.capsule;
            shape.capsule = &capsule;
            capsule.segment.start.y += 0x28000;
            capsule.segment.end.y -= 0x28000;
            InitSegmentFromEndpoints(&capsule.segment);
            PlaceShape(&shape, VecAdd(&shape.capsule->segment.start, &mover->velocity));
            if (TestShapeAgainstEntry(&shape, ref, &contact)) {
                s64 zz;
                s64 xx;
                fx32 horizontalLen;

                pushDir = GetPlanar(&contact.normal);
                SafeNormalizeXy(&pushDir);
                pushMag = VEC_Mag(&body->push);
                zz = normal->z;
                xx = normal->x;
                horizontalLen =
                    FX_Sqrt((u32)((_ll_mul(xx, xx) + _ll_mul(zz, zz)) >> 12));
                if (horizontalLen < 0x800) {
                    horizontalLen = 0x800;
                }
                speed = FX_Mul(0x200, 0x1000 - horizontalLen);
                body->push.x += FX_Mul(pushDir.x, speed);
                body->push.z += FX_Mul(pushDir.z, speed);
                if (pushMag != 0) {
                    if (pushMag < speed) {
                        pushMag = speed;
                    }
                    func_01ffaff4(&body->push, &body->push);
                    ScaleVecFx32InPlace(&body->push, pushMag);
                }
                body->flags |= 0x80;
            }
        }
    }
}
