#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionSphere {
    VecFx32 center;
    fx32 radius;
} CollisionSphere;

typedef struct CollisionCylinder {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
    fx32 radius;
} CollisionCylinder;

typedef struct SweepResult {
    u32 enterTimeLo;
    s32 enterTimeHi;
    u32 exitTimeLo;
    s32 exitTimeHi;
    VecFx32 enterAxis;
    fx32 minDepth;
    VecFx32 depthAxis;
    s8 depthSign;
    u8 depthFeature;
    u8 pad_2E[2];
    s8 enterSign;
    u8 touching;
    u8 enterFeature;
    u8 pad_33;
} SweepResult;

extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void func_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void InitHitQuery(SweepResult *result);
extern fx32 ComputeDirectionalExtent(const CollisionCylinder *cylinder, const VecFx32 *dirA, s32 majorExtent, const VecFx32 *dirB);
extern fx32 func_02047198(const CollisionSphere *sphere, const VecFx32 *dir, const VecFx32 *endpoint, fx32 rimRadius, fx32 sphereRadius, const VecFx32 *axis, fx32 *roots, VecFx32 *normal);
extern BOOL SweepIntervalOnAxis(fx32 extent, fx32 distance, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime);
extern BOOL ResolveSweepContact(SweepResult *result, void *contact, u32 flags, const VecFx32 *velocity);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void GetUnitCross(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);
extern fx32 BlendVectorsBySqrtComplement(VecFx32 *a, const VecFx32 *b, fx32 t, s8 factor, VecFx32 *out);
extern VecFx32 AverageVecs(s32 count, ...);

static inline SweepResult MakeSweepResult(void)
{
    SweepResult result;
    InitHitQuery(&result);
    return result;
}

static inline VecFx32 VecSub(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 diff;
    func_01ff9e3c(a, b, &diff);
    return diff;
}

static inline VecFx32 UnitVector(const VecFx32 *v)
{
    VecFx32 unit;
    func_01ffaff4(v, &unit);
    return unit;
}

static inline VecFx32 PerpAxis(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 perp;
    GetUnitCross(&perp, a, b);
    return perp;
}

static inline VecFx32 Cross(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 cross;
    func_01ff9ea8(a, b, &cross);
    return cross;
}

static inline VecFx32 RejectFromAxis(const VecFx32 *v, const VecFx32 *axis)
{
    VecFx32 projection;
    VecFx32 scaledAxis;
    VecFx32 rejection;
    fx32 dot = VEC_DotProduct(v, axis);

    scaledAxis = *axis;
    ScaleVecFx32InPlace(&scaledAxis, dot);
    projection = scaledAxis;
    func_01ff9e3c(v, &projection, &rejection);
    return rejection;
}

static inline s32 Sign(fx32 value)
{
    return value == 0 ? 0 : (value > 0 ? 1 : -1);
}

BOOL SweepSphereAgainstCappedCylinder(CollisionSphere **sphereRef, CollisionCylinder **cylinderRef, void *contact, u32 flags, const VecFx32 *velocity)
{
    CollisionSphere *sphere = *sphereRef;
    CollisionCylinder *cylinder = *cylinderRef;
    SweepResult result = MakeSweepResult();
    VecFx32 normal;
    VecFx32 center = AverageVecs(2, &cylinder->start, &cylinder->end);
    VecFx32 diff = VecSub(&sphere->center, &center);
    VecFx32 axis = cylinder->direction;
    fx32 length = cylinder->length;
    VecFx32 dir = UnitVector(velocity);
    VecFx32 side = PerpAxis(&axis, &dir);
    VecFx32 perp = Cross(&side, &axis);
    VecFx32 radial;
    VecFx32 endpoint;
    fx32 roots[12];
    VecFx32 hitNormal;
    fx32 extent;
    fx32 sideDot;
    fx32 sideDistance;
    fx32 sum;
    fx32 weight;
    u8 i;

    sideDot = VEC_DotProduct(&diff, &side);
    sideDistance = sideDot < 0 ? -sideDot : sideDot;
    sum = sphere->radius + cylinder->radius;
    radial = RejectFromAxis(&diff, &axis);
    weight = Sign(sideDot) * (sideDistance < sum ? FX_Div(sideDistance, sum) : 0x1000);
    BlendVectorsBySqrtComplement(&side, &perp, weight, VEC_DotProduct(&dir, &radial) >= 0 ? 1 : -1, &normal);
    if (!SweepIntervalOnAxis(sum, VEC_DotProduct(&normal, &diff), &normal, 3, velocity, &result, NULL)) {
        return FALSE;
    }

    normal = axis;
    extent = sphere->radius + length / 2;
    if (!SweepIntervalOnAxis(extent, VEC_DotProduct(&normal, &diff), &normal, 0, velocity, &result, NULL)) {
        return FALSE;
    }

    for (i = 0; i < 2; i++) {
        endpoint = i == 0 ? cylinder->start : cylinder->end;
        if (func_02047198(sphere, &dir, &endpoint, cylinder->radius, sphere->radius, &axis, roots, &hitNormal) != 0x7fffffff) {
            normal = hitNormal;
        } else {
            normal = PerpAxis(&dir, &axis);
            normal = Cross(&normal, &dir);
            VEC_Normalize(&normal, &normal);
        }
        extent = ComputeDirectionalExtent(cylinder, &axis, length, &normal);
        extent += sphere->radius;
        if (!SweepIntervalOnAxis(extent, VEC_DotProduct(&normal, &diff), &normal, 3, velocity, &result, NULL)) {
            return FALSE;
        }
    }
    return ResolveSweepContact(&result, contact, flags, velocity);
}
