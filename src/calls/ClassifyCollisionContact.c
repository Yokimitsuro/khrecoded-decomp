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
    void *unk_48;
} Surface;

typedef struct SurfaceRef {
    Surface *surface;
    s32 kind;
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
    u8 pad_08[0x24];
    s32 unk_2C;
    u8 pad_30[0x18];
    Surface *ground;
    u8 pad_4C[0xbc];
    s32 groundKind;
} Body;

typedef struct ContactState {
    Body *body;
    u32 pad_04;
    VecFx32 floorNormal;
    VecFx32 wallNormal;
    VecFx32 ceilingNormal;
    u32 pad_2C;
    u32 flags;
    s32 landed;
} ContactState;

typedef struct CollBox {
    fx32 maxX;
    fx32 maxY;
    fx32 maxZ;
    fx32 minX;
    fx32 minY;
    fx32 minZ;
} CollBox;

typedef struct CollSegment {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
} CollSegment;

typedef struct CollShape {
    CollSegment *segment;
    CollBox box;
    s32 kind;
} CollShape;

typedef struct CollSweep {
    CollShape shape;
    VecFx32 delta;
    CollBox sweepBox;
} CollSweep;

typedef struct Capsule {
    CollSegment segment;
    fx32 radius;
} Capsule;

typedef struct Mover {
    Capsule *capsule;
    u8 pad_04[0x1c];
    VecFx32 velocity;
} Mover;

extern s16 data_02053800[];
extern s16 data_02053b80[];
extern s16 data_02053980;

extern BOOL IsFacingContactNormal(SurfaceRef *ref, const VecFx32 *normal);
extern void InitSegmentFromEndpoints(CollSegment *segment);
extern BOOL TestSweepAgainstTarget(CollSweep *sweep, SurfaceRef *ref, ContactPlane *contact);
extern s32 ContainsMatchingEntry(SurfaceRef *ref, u32 kind);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern fx32 FX_Sqrt(u32 value);
/* Explicit _ll_mul call keeps the runtime helper bound. */
extern s64 _ll_mul(s64 a, s64 b);
extern fx32 FX_Mul(fx32 left, fx32 right);
extern void GetUnitRejectionFromAxis(VecFx32 *out, const VecFx32 *v, const VecFx32 *normal);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void ScaleVecHighShift(VecFx32 *vec, s32 scale);
extern fx32 AbsDotProduct(const VecFx32 *a, const VecFx32 *b);
extern s32 func_ov001_02063a4c(void);
extern s32 func_ov001_02063a38(void);
extern VecFx32 *GetModeContext(void);
extern void SetPlaneNormalRescaled(ContactPlane *contact, const VecFx32 *normal);

static inline VecFx32 VecS16ToFx32(const VecS16 *src)
{
    VecFx32 result;
    result.x = src->x;
    result.y = src->y;
    result.z = src->z;
    return result;
}

static inline BOOL VecEquals(const VecFx32 *a, const VecFx32 *b)
{
    return a->x == b->x && a->y == b->y && a->z == b->z;
}

static inline VecFx32 ScaledVec(const VecFx32 *src, s32 scale)
{
    VecFx32 result = *src;
    ScaleVecHighShift(&result, scale);
    return result;
}

static inline BOOL IsMode4(void)
{
    return func_ov001_02063a38() == 4;
}

static inline BOOL IsMode7(void)
{
    return func_ov001_02063a38() == 7;
}

static inline BOOL IsMode4Or7(void)
{
    return IsMode4() || IsMode7();
}

static inline BOOL ShouldAlignToModeNormal(void)
{
    return func_ov001_02063a4c() >= 4 && func_ov001_02063a4c() <= 9 && IsMode4Or7();
}

static inline VecFx32 VecMultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add)
{
    VecFx32 result;
    VEC_MultAdd(scale, v, add, &result);
    return result;
}

BOOL ClassifyCollisionContact(SurfaceRef *ref, ContactPlane *contact, ContactState *state, Mover *mover)
{
    CollSweep sweep;
    CollSegment segment;
    VecFx32 scaledVelocity;
    VecFx32 surfaceNormal;
    VecFx32 groundNormal;
    VecFx32 projected;
    VecFx32 slopeNormal;
    VecFx32 wallGroundNormal;
    VecFx32 adjusted;
    Body *body;
    const VecFx32 *expected;
    s32 floorLimit;
    s32 kind;
    BOOL isFloor;

    if (!IsFacingContactNormal(ref, &contact->normal)) {
        return FALSE;
    }
    body = state->body;
    floorLimit = data_02053800[0x15];
    kind = ref->kind;
    if (kind == 4) {
        isFloor = (contact->normal.y > floorLimit && (contact->surfaceType & 3) == 0);
    } else {
        isFloor = (kind == 1);
    }

    if (isFloor) {
        if (contact->normal.y == 0x1000) {
            body->flags |= 4;
            if (ref->kind == 4) {
                body->groundKind = 1;
            } else {
                body->groundKind = 2;
            }
            state->floorNormal = contact->normal;
            goto finish;
        }
        segment = mover->capsule->segment;
        sweep.shape.segment = &segment;
        sweep.shape.kind = 2;
        sweep.delta = mover->velocity;
        segment.start.y += mover->capsule->radius - 0x10;
        segment.end.y -= mover->capsule->radius - 0x10;
        InitSegmentFromEndpoints(&segment);
        if (TestSweepAgainstTarget(&sweep, ref, contact)) {
            surfaceNormal = VecS16ToFx32(&ref->surface->normal);
            expected = &surfaceNormal;
            if (VecEquals(&contact->normal, expected)) {
                body->flags |= 4;
                if (ref->kind == 4) {
                    body->groundKind = 1;
                } else {
                    body->groundKind = 2;
                }
                state->floorNormal = contact->normal;
            } else {
                if ((contact->normal.y < 0 ? -contact->normal.y : contact->normal.y) < 0x10) {
                    return FALSE;
                }
                if (contact->normal.y != 0 && ContainsMatchingEntry(ref, 5)) {
                    mover->velocity = VecMultAdd(contact->distance, &contact->normal, &mover->velocity);
                    mover->velocity.y -= 0x80;
                    return FALSE;
                }
            }
            return TRUE;
        }
        return FALSE;
    }

    if ((contact->surfaceType & 3) == 0 &&
        (kind == 3 || (kind == 4 && contact->normal.y < -data_02053b80[0x1c]))) {
        body->flags |= 8;
        if (ref->kind == 4) {
            body->flags |= 0x1000;
        }
        state->ceilingNormal = contact->normal;
        if (contact->normal.y < -data_02053b80[0x1c] && body->unk_2C > 0) {
            body->unk_2C = 0;
        }
        goto finish;
    }

    if (state->flags & 4) {
        BOOL slide = FALSE;
        switch (kind) {
        case 2:
            if (contact->normal.y > 0) {
                slide = TRUE;
            }
            break;
        case 4:
            if (contact->normal.y > 0 &&
                (ref->surface->unk_0D == 0 || ref->surface->unk_48 == NULL)) {
                slide = TRUE;
            }
            break;
        case 1:
            if ((state->flags & 4) && body->ground != NULL) {
                groundNormal = VecS16ToFx32(&body->ground->normal);
                if (VEC_DotProduct(&contact->normal, &groundNormal) <= 0xff0) {
                    slide = TRUE;
                }
            }
            break;
        }
        if (slide) {
            if ((contact->surfaceType & 3) != 0 && (contact->surfaceType & 2) == 0) {
                fx32 approach = -VEC_DotProduct(&mover->velocity, &contact->normal);
                s64 normalZ = contact->normal.z;
                s64 normalX = contact->normal.x;
                fx32 horizontal = FX_Mul(contact->distance,
                    FX_Sqrt((u32)((_ll_mul(normalX, normalX) + _ll_mul(normalZ, normalZ)) >> 12)));
                if (horizontal - approach < 0x52 && contact->normal.y > data_02053980) {
                    return FALSE;
                }
            }
            if (body->ground != NULL) {
                slopeNormal = VecS16ToFx32(&body->ground->normal);
                GetUnitRejectionFromAxis(&projected, &contact->normal, &slopeNormal);
                contact->normal = projected;
            } else {
                contact->normal.y = 0;
                VEC_Normalize(&contact->normal, &contact->normal);
            }
            if (contact->time <= 0) {
                contact->distance = AbsDotProduct(&mover->velocity, &contact->normal);
            } else {
                scaledVelocity = ScaledVec(&mover->velocity, 0x8000000 - contact->time);
                contact->distance = AbsDotProduct(&scaledVelocity, &contact->normal);
            }
        }
    }

    if ((state->flags & 4) && body->ground != NULL) {
        wallGroundNormal = VecS16ToFx32(&body->ground->normal);
        if (VEC_DotProduct(&contact->normal, &wallGroundNormal) > 0xf80) {
            return FALSE;
        }
    }
    body->flags |= 2;
    state->wallNormal = contact->normal;

finish:
    if (ShouldAlignToModeNormal()) {
        GetUnitRejectionFromAxis(&adjusted, &contact->normal, GetModeContext());
        SetPlaneNormalRescaled(contact, &adjusted);
    }
    if (IsMode4() && contact->time == -1 && contact->distance > 0x10) {
        state->landed = 1;
    }
    return TRUE;
}
