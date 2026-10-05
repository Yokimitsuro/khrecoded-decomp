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

typedef struct SphereShapeRef {
    CollisionSphere *sphere;
} SphereShapeRef;

typedef struct CylinderShapeRef {
    CollisionCylinder *cylinder;
} CylinderShapeRef;

typedef struct CollisionHit {
    fx32 depth;
    VecFx32 normal;
    fx32 time;
    u8 kind;
} CollisionHit;

typedef struct Vec2Fx32 {
    fx32 x;
    fx32 y;
} Vec2Fx32;

extern fx32 FX_Sqrt(fx32 value);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern fx32 func_01ffaff4(VecFx32 *src, VecFx32 *dst);
extern int PXI_Init_0203f23c(int value);
extern fx32 Vec_DotSelf(const VecFx32 *v);
extern fx32 SquareFx32ToFx64(fx32 value);
extern VecFx32 VecFx32DividedByScalar(const VecFx32 *v, fx32 divisor);
extern fx32 DivideShifted27(fx32 numer, fx32 denom);
extern VecFx32 VecFx32ScaledCopy(const VecFx32 *v, fx32 scale);
extern VecFx32 ComputeNormalizedCrossInto(const VecFx32 *v);
extern VecFx32 NormalizeVectorInto(const VecFx32 *src);
extern VecFx32 GetSegmentDirection(const CollisionCylinder *cylinder);
extern VecFx32 AddVecFx32Into(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 NegateVecFx32Into(const VecFx32 *src);
extern s32 MinFx32(s32 a, s32 b);
extern fx32 FX_Div_0203fa00(fx32 a, fx32 b);
extern fx32 NormalizeXy(Vec2Fx32 *vec);
extern void NegateVecFx32(VecFx32 *vec);

BOOL TestSphereAgainstCylinder(SphereShapeRef *sphereRef, CylinderShapeRef *cylinderRef, CollisionHit *hit, u32 flags)
{
    CollisionSphere *sphere = sphereRef->sphere;
    CollisionCylinder *cylinder = cylinderRef->cylinder;
    VecFx32 axis = GetSegmentDirection(cylinder);
    fx32 length = func_01ffaff4(&axis, &axis);
    fx32 dotCenter = VEC_DotProduct(&axis, &sphere->center);
    fx32 dotStart = VEC_DotProduct(&axis, &cylinder->start);
    fx32 dotEnd = VEC_DotProduct(&axis, &cylinder->end);
    VecFx32 toCenter;
    fx32 sqDistance;

    if (dotCenter < dotStart - sphere->radius || dotCenter > dotEnd + sphere->radius) {
        return FALSE;
    }
    toCenter = AddVecFx32Into(&cylinder->start, &VecFx32ScaledCopy(&axis, dotCenter - dotStart));
    VEC_Subtract(&toCenter, &sphere->center, &toCenter);
    sqDistance = Vec_DotSelf(&toCenter);
    if ((dotCenter > dotStart) != (dotCenter > dotEnd)) {
        fx32 radiusSum = sphere->radius + cylinder->radius;
        if (sqDistance > SquareFx32ToFx64(radiusSum)) {
            return FALSE;
        }
        if (hit != NULL) {
            if (sqDistance != 0) {
                sqDistance = FX_Sqrt(sqDistance);
                hit->depth = radiusSum - sqDistance;
                hit->normal = VecFx32DividedByScalar(&toCenter, sqDistance);
                if (!(flags & 1)) {
                    NegateVecFx32(&hit->normal);
                }
            } else {
                hit->depth = radiusSum;
                hit->normal = ComputeNormalizedCrossInto(&axis);
            }
            hit->kind = 3;
            hit->time = DivideShifted27(dotCenter - dotStart, length);
        } else {
            return TRUE;
        }
    } else if (hit != NULL) {
        hit->depth = 0x7FFFFFFF;
    }
    {
        fx32 offset = dotCenter - (dotStart + length / 2);
        fx32 absOffset = PXI_Init_0203f23c(offset);

        if (absOffset <= length / 2 + sphere->radius) {
            if (absOffset <= length / 2) {
                fx32 capDepth = length / 2 + sphere->radius - absOffset;
                if (hit->depth > capDepth) {
                    hit->depth = capDepth;
                    if (offset >= 0) {
                        hit->normal = axis;
                        hit->time = 0x8000000;
                    } else {
                        hit->normal = NegateVecFx32Into(&axis);
                        hit->time = 0;
                    }
                    hit->kind = 0;
                    if (flags & 1) {
                        NegateVecFx32(&hit->normal);
                    }
                }
                return TRUE;
            } else {
                fx32 distStart = PXI_Init_0203f23c(dotCenter - dotStart);
                fx32 distEnd = PXI_Init_0203f23c(dotCenter - dotEnd);
                fx32 capDistance = MinFx32(distStart, distEnd);
                fx32 rimRadius = FX_Sqrt(SquareFx32ToFx64(sphere->radius) - SquareFx32ToFx64(capDistance));

                if (sqDistance > SquareFx32ToFx64(rimRadius + cylinder->radius)) {
                    return FALSE;
                }
                if (hit != NULL) {
                    fx32 distance = FX_Sqrt(sqDistance);
                    if (distance > cylinder->radius) {
                        fx32 excess = distance - cylinder->radius;
                        fx32 depth = sphere->radius - FX_Div_0203fa00(excess, capDistance);
                        if (hit->depth > depth) {
                            Vec2Fx32 edge;
                            hit->depth = depth;
                            edge.x = excess;
                            edge.y = capDistance;
                            NormalizeXy(&edge);
                            hit->normal = VecFx32ScaledCopy(&NormalizeVectorInto(&toCenter), -edge.x);
                            if (distEnd < distStart) {
                                VEC_Add(&hit->normal, &VecFx32ScaledCopy(&axis, edge.y), &hit->normal);
                            } else {
                                VEC_Add(&hit->normal, &VecFx32ScaledCopy(&axis, -edge.y), &hit->normal);
                            }
                        } else {
                            return TRUE;
                        }
                    } else {
                        fx32 depth = sphere->radius - capDistance;
                        if (hit->depth > depth) {
                            hit->depth = depth;
                            if (distEnd < distStart) {
                                hit->normal = axis;
                            } else {
                                hit->normal = NegateVecFx32Into(&axis);
                            }
                        } else {
                            return TRUE;
                        }
                    }
                    if (flags & 1) {
                        NegateVecFx32(&hit->normal);
                    }
                    hit->kind = 3;
                    hit->time = distEnd < distStart ? 0x8000000 : 0;
                }
                return TRUE;
            }
        }
        return FALSE;
    }
}
